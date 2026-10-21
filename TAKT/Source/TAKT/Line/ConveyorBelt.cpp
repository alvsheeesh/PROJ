#include "Line/ConveyorBelt.h"

#include "TAKT.h"

#include "CollisionQueryParams.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/CollisionProfile.h"
#include "Engine/OverlapResult.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "UObject/ConstructorHelpers.h"

namespace
{
	// El cubo básico del motor mide 100 cm de lado, con el pivote en el centro.
	constexpr float BasicCubeSize = 100.f;

	// Por debajo de esta diferencia (1 cm/s) no se toca el cuerpo, para que lo
	// que está quieto sobre una cinta parada pueda dormirse.
	constexpr float MinVelocityDeltaSquared = 1.f;
}

AConveyorBelt::AConveyorBelt()
{
	PrimaryActorTick.bCanEverTick = true;
	// Antes de la física: la velocidad que se pone aquí la usa la simulación de este mismo frame.
	PrimaryActorTick.TickGroup = TG_PrePhysics;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BeltMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeltMesh"));
	BeltMesh->SetupAttachment(Root);
	BeltMesh->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		BeltMesh->SetStaticMesh(CubeMesh.Object);
	}

	CarryZone = CreateDefaultSubobject<UBoxComponent>(TEXT("CarryZone"));
	CarryZone->SetupAttachment(Root);
	CarryZone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CarryZone->SetGenerateOverlapEvents(false);
	CarryZone->SetHiddenInGame(true);
	CarryZone->ShapeColor = FColor::Cyan;

#if WITH_EDITORONLY_DATA
	DirectionArrow = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
	if (DirectionArrow)
	{
		DirectionArrow->SetupAttachment(Root);
		DirectionArrow->ArrowColor = FColor::Yellow;
		DirectionArrow->SetRelativeLocation(FVector(0.f, 0.f, 1.f));
	}
#endif

	UpdateLayout();
}

void AConveyorBelt::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UpdateLayout();
}

void AConveyorBelt::BeginPlay()
{
	Super::BeginPlay();

	UPhysicalMaterial* Surface = SurfaceMaterial;
	if (!Surface)
	{
		// Sin fricción y con combinación "Min": el rozamiento entre la cinta y
		// cualquier objeto es 0, sea cual sea el material del objeto.
		Surface = NewObject<UPhysicalMaterial>(this, TEXT("PM_ConveyorBeltFrictionless"));
		Surface->Friction = 0.f;
		Surface->StaticFriction = 0.f;
		Surface->FrictionCombineMode = EFrictionCombineMode::Min;
		Surface->bOverrideFrictionCombineMode = true;
		Surface->Restitution = 0.f;
	}
	BeltMesh->SetPhysMaterialOverride(Surface);

	SetRunning(bStartRunning);
}

void AConveyorBelt::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CarryBodies(DeltaSeconds);
}

void AConveyorBelt::SetRunning(bool bInRunning)
{
	if (bRunning == bInRunning)
	{
		return;
	}

	bRunning = bInRunning;
	UE_LOG(LogTAKT, Verbose, TEXT("%s: %s"), *GetName(), bRunning ? TEXT("en marcha") : TEXT("parada"));
}

void AConveyorBelt::ToggleRunning()
{
	SetRunning(!bRunning);
}

void AConveyorBelt::UpdateLayout()
{
	// La superficie queda en Z = 0 del actor: la malla por debajo y la zona por encima.
	BeltMesh->SetRelativeScale3D(FVector(BeltSize.X, BeltSize.Y, Thickness) / BasicCubeSize);
	BeltMesh->SetRelativeLocation(FVector(0.f, 0.f, -Thickness * 0.5f));

	CarryZone->SetBoxExtent(FVector(BeltSize.X * 0.5f, BeltSize.Y * 0.5f, CarryHeight * 0.5f), false);
	CarryZone->SetRelativeLocation(FVector(0.f, 0.f, CarryHeight * 0.5f));

#if WITH_EDITORONLY_DATA
	if (DirectionArrow)
	{
		DirectionArrow->ArrowLength = BeltSize.X * 0.5f;
	}
#endif
}

void AConveyorBelt::CarryBodies(float DeltaSeconds)
{
	UWorld* World = GetWorld();
	if (!World || DeltaSeconds <= 0.f)
	{
		return;
	}

	const FVector Direction = GetActorForwardVector().GetSafeNormal2D();
	const FVector TargetVelocity = bRunning ? Direction * Speed : FVector::ZeroVector;

	// Aproximación exponencial: se comporta igual a 72, 90 o 120 fps.
	const float Alpha = 1.f - FMath::Exp(-Grip * DeltaSeconds);

	// Consulta de solapamiento en vez de eventos de overlap: no depende de que
	// los objetos tengan activado "Generate Overlap Events".
	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	ObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(ConveyorBelt), false, this);

	TArray<FOverlapResult> Overlaps;
	World->OverlapMultiByObjectType(
		Overlaps,
		CarryZone->GetComponentLocation(),
		CarryZone->GetComponentQuat(),
		ObjectParams,
		CarryZone->GetCollisionShape(),
		QueryParams);

	TSet<UPrimitiveComponent*> Carried;
	for (const FOverlapResult& Overlap : Overlaps)
	{
		UPrimitiveComponent* Body = Overlap.GetComponent();
		if (!Body || !Body->IsSimulatingPhysics())
		{
			continue;
		}

		bool bAlreadyCarried = false;
		Carried.Add(Body, &bAlreadyCarried);
		if (bAlreadyCarried)
		{
			continue;
		}

		const FVector Velocity = Body->GetPhysicsLinearVelocity();
		const FVector Horizontal(Velocity.X, Velocity.Y, 0.f);
		const FVector Delta = TargetVelocity - Horizontal;
		if (Delta.SizeSquared() < MinVelocityDeltaSquared)
		{
			continue;
		}

		// Solo la parte horizontal: la gravedad y los botes siguen siendo cosa de la física.
		const FVector NewHorizontal = Horizontal + Delta * Alpha;
		Body->SetPhysicsLinearVelocity(FVector(NewHorizontal.X, NewHorizontal.Y, Velocity.Z));
	}

#if ENABLE_DRAW_DEBUG
	if (bDrawDebug)
	{
		DrawDebugBox(World, CarryZone->GetComponentLocation(), CarryZone->GetScaledBoxExtent(),
			CarryZone->GetComponentQuat(), bRunning ? FColor::Green : FColor::Red, false, -1.f, 0, 1.f);

		for (const UPrimitiveComponent* Body : Carried)
		{
			DrawDebugPoint(World, Body->GetComponentLocation(), 10.f, FColor::Yellow, false, -1.f);
		}
	}
#endif
}
