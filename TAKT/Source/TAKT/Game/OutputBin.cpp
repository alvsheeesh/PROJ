#include "Game/OutputBin.h"

#include "TAKT.h"

#include "CollisionQueryParams.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/OverlapResult.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Interaction/GrabbableComponent.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

namespace
{
	constexpr float WallThickness = 2.f;
}

AOutputBin::AOutputBin()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.05f;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	Bottom = CreatePart(TEXT("Bottom"));
	WallFront = CreatePart(TEXT("WallFront"));
	WallBack = CreatePart(TEXT("WallBack"));
	WallLeft = CreatePart(TEXT("WallLeft"));
	WallRight = CreatePart(TEXT("WallRight"));

	Zone = CreateDefaultSubobject<UBoxComponent>(TEXT("Zone"));
	Zone->SetupAttachment(GetRootComponent());
	Zone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Zone->SetGenerateOverlapEvents(false);
}

UStaticMeshComponent* AOutputBin::CreatePart(const FName Name)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));

	UStaticMeshComponent* Part = CreateDefaultSubobject<UStaticMeshComponent>(Name);
	Part->SetupAttachment(GetRootComponent());
	Part->SetStaticMesh(CubeMesh.Object);
	Part->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	return Part;
}

void AOutputBin::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// La forma básica mide 100 cm: escala = medida / 100.
	const FVector Size = BinSize.ComponentMax(FVector(10.f));
	const float T = WallThickness;

	Bottom->SetRelativeLocation(FVector(0.f, 0.f, T * 0.5f));
	Bottom->SetRelativeScale3D(FVector(Size.X, Size.Y, T) / 100.f);

	WallFront->SetRelativeLocation(FVector(Size.X * 0.5f, 0.f, Size.Z * 0.5f));
	WallFront->SetRelativeScale3D(FVector(T, Size.Y, Size.Z) / 100.f);

	WallBack->SetRelativeLocation(FVector(-Size.X * 0.5f, 0.f, Size.Z * 0.5f));
	WallBack->SetRelativeScale3D(FVector(T, Size.Y, Size.Z) / 100.f);

	WallLeft->SetRelativeLocation(FVector(0.f, -Size.Y * 0.5f, Size.Z * 0.5f));
	WallLeft->SetRelativeScale3D(FVector(Size.X, T, Size.Z) / 100.f);

	WallRight->SetRelativeLocation(FVector(0.f, Size.Y * 0.5f, Size.Z * 0.5f));
	WallRight->SetRelativeScale3D(FVector(Size.X, T, Size.Z) / 100.f);

	Zone->SetRelativeLocation(FVector(0.f, 0.f, Size.Z * 0.5f));
	Zone->SetBoxExtent(FVector(Size.X - T, Size.Y - T, Size.Z) * 0.5f);
}

void AOutputBin::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(PendingTimer);
	}
	Super::EndPlay(EndPlayReason);
}

void AOutputBin::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Counted.RemoveAll([](const TWeakObjectPtr<AActor>& Product) { return !Product.IsValid(); });

	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	ObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(OutputBin), false, this);

	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByObjectType(
		Overlaps,
		Zone->GetComponentLocation(),
		Zone->GetComponentQuat(),
		ObjectParams,
		Zone->GetCollisionShape(),
		QueryParams);

	for (const FOverlapResult& Overlap : Overlaps)
	{
		AActor* Product = Overlap.GetActor();
		if (!Product || Counted.Contains(Product))
		{
			continue;
		}

		const UGrabbableComponent* Grabbable = Product->FindComponentByClass<UGrabbableComponent>();
		if (!Grabbable || Grabbable->IsHeld())
		{
			continue;
		}

		Counted.Add(Product);
		Deliver(Product);
	}
}

void AOutputBin::Deliver(AActor* Product)
{
	FTimerManager& Timers = GetWorld()->GetTimerManager();

	if (Timers.IsTimerActive(PendingTimer))
	{
		Timers.ClearTimer(PendingTimer);
		++Pairs;
		UE_LOG(LogTAKT, Log, TEXT("%s: pareja (%d)."), *GetName(), Pairs);
		OnPairDelivered.Broadcast();
	}
	else
	{
		Timers.SetTimer(PendingTimer, this, &AOutputBin::ExpirePending, PairWindow, false);
	}

	Product->SetLifeSpan(FMath::Max(RemoveDelay, 0.01f));
}

void AOutputBin::ExpirePending()
{
	++Singles;
	UE_LOG(LogTAKT, Log, TEXT("%s: producto suelto (%d)."), *GetName(), Singles);
	OnSingleDelivered.Broadcast();
}
