#include "Line/Lever.h"

#include "TAKT.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Interaction/ActuatableComponent.h"
#include "Line/LineController.h"
#include "UObject/ConstructorHelpers.h"

ALever::ALever()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	// Las formas básicas miden 100 cm: base de 30×30×10 cm, mango de 5×40 cm y pomo de 10 cm.
	// El origen del actor queda en la parte de abajo de la base.
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	Base->SetupAttachment(GetRootComponent());
	Base->SetStaticMesh(CubeMesh.Object);
	Base->SetRelativeLocation(FVector(0.f, 0.f, 5.f));
	Base->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.1f));
	Base->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	Pivot->SetupAttachment(GetRootComponent());
	Pivot->SetMobility(EComponentMobility::Movable);
	Pivot->SetRelativeLocation(FVector(0.f, 0.f, 10.f));

	Handle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Handle"));
	Handle->SetupAttachment(Pivot);
	Handle->SetMobility(EComponentMobility::Movable);
	Handle->SetStaticMesh(CylinderMesh.Object);
	Handle->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
	Handle->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.4f));
	Handle->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	Knob = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Knob"));
	Knob->SetupAttachment(Pivot);
	Knob->SetMobility(EComponentMobility::Movable);
	Knob->SetStaticMesh(SphereMesh.Object);
	Knob->SetRelativeLocation(FVector(0.f, 0.f, 40.f));
	Knob->SetRelativeScale3D(FVector(0.1f));
	Knob->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	Actuatable = CreateDefaultSubobject<UActuatableComponent>(TEXT("Actuatable"));
}

void ALever::BeginPlay()
{
	Super::BeginPlay();

	if (!Line)
	{
		UE_LOG(LogTAKT, Warning, TEXT("%s: no tiene ninguna línea asignada."), *GetName());
	}

	Actuatable->OnActuated.AddDynamic(this, &ALever::HandleActuated);
}

void ALever::Actuate()
{
	Actuatable->Actuate(nullptr);
}

void ALever::HandleActuated(UHandComponent* Hand)
{
	AnimationTime = 0.f;
	SetActorTickEnabled(true);

	if (!Line)
	{
		return;
	}

	if (Line->GetState() != ELineState::Faulted)
	{
		UE_LOG(LogTAKT, Log, TEXT("%s: no hay ninguna avería que reparar."), *GetName());
#if !UE_BUILD_SHIPPING
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, TEXT("Palanca: no hay ninguna avería que reparar"));
		}
#endif
		return;
	}

	Line->Repair();
	if (bStartAfterRepair)
	{
		Line->Start();
	}
}

void ALever::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (AnimationTime < 0.f)
	{
		SetActorTickEnabled(false);
		return;
	}

	AnimationTime += DeltaSeconds;
	const float Alpha = FMath::Clamp(AnimationTime / AnimationDuration, 0.f, 1.f);
	// Baja y vuelve a subir: 0 -> PulledAngle -> 0.
	const float Angle = PulledAngle * FMath::Sin(Alpha * UE_PI);
	Pivot->SetRelativeRotation(FRotator(Angle, 0.f, 0.f));

	if (Alpha >= 1.f)
	{
		Pivot->SetRelativeRotation(FRotator::ZeroRotator);
		AnimationTime = -1.f;
		SetActorTickEnabled(false);
	}
}
