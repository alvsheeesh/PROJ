#include "Game/ProductDispenser.h"

#include "TAKT.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Interaction/GrabbableComponent.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

AProductDispenser::AProductDispenser()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	static ConstructorHelpers::FClassFinder<AActor> DefaultProduct(TEXT("/Game/XRFramework/Blueprints/BP_Grabbable_SmallCube"));
	if (DefaultProduct.Succeeded())
	{
		ProductClass = DefaultProduct.Class;
	}

	// El origen del actor queda en la parte de abajo de la bandeja.
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	// Bandeja de 30×30×2 cm.
	Tray = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tray"));
	Tray->SetupAttachment(GetRootComponent());
	Tray->SetStaticMesh(CubeMesh.Object);
	Tray->SetRelativeLocation(FVector(0.f, 0.f, 1.f));
	Tray->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.02f));
	Tray->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(GetRootComponent());
	SpawnPoint->SetRelativeLocation(FVector(0.f, 0.f, 12.f));
}

void AProductDispenser::BeginPlay()
{
	Super::BeginPlay();

	if (!ProductClass)
	{
		UE_LOG(LogTAKT, Warning, TEXT("%s: no tiene Product Class."), *GetName());
		return;
	}
	SpawnProduct();

	// Si el producto se cae de la bandeja sin que nadie lo coja, se da por perdido y se repone.
	FTimerHandle LostCheckTimer;
	GetWorld()->GetTimerManager().SetTimer(LostCheckTimer, FTimerDelegate::CreateWeakLambda(this, [this]()
	{
		constexpr float MaxDistanceFromTray = 25.f;
		if (CurrentProduct && FVector::Dist(CurrentProduct->GetActorLocation(), SpawnPoint->GetComponentLocation()) > MaxDistanceFromTray)
		{
			UE_LOG(LogTAKT, Log, TEXT("%s: %s se ha caído de la bandeja; se repone."), *GetName(), *CurrentProduct->GetName());
			ReleaseCurrent();
			ScheduleRefill();
		}
	}), 0.25f, true);
}

void AProductDispenser::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearAllTimersForObject(this);
	}
	Super::EndPlay(EndPlayReason);
}

void AProductDispenser::Dispense()
{
	if (!HasActorBegunPlay())
	{
		return;
	}
	ReleaseCurrent();
	ScheduleRefill();
}

void AProductDispenser::HandleProductGrabbed(UHandComponent* Hand)
{
	ReleaseCurrent();
	ScheduleRefill();
}

void AProductDispenser::HandleProductDestroyed(AActor* DestroyedActor)
{
	// Si se pierde el producto de la bandeja sin cogerlo, se repone igual.
	if (DestroyedActor == CurrentProduct)
	{
		CurrentProduct = nullptr;
		ScheduleRefill();
	}
}

void AProductDispenser::ScheduleRefill()
{
	FTimerManager& Timers = GetWorld()->GetTimerManager();
	if (!Timers.IsTimerActive(RefillTimer))
	{
		Timers.SetTimer(RefillTimer, this, &AProductDispenser::SpawnProduct, FMath::Max(RefillDelay, 0.01f), false);
	}
}

void AProductDispenser::ReleaseCurrent()
{
	if (!CurrentProduct)
	{
		return;
	}
	if (UGrabbableComponent* Grabbable = CurrentProduct->FindComponentByClass<UGrabbableComponent>())
	{
		Grabbable->OnGrabbed.RemoveDynamic(this, &AProductDispenser::HandleProductGrabbed);
	}
	CurrentProduct = nullptr;
}

void AProductDispenser::MakeRoom()
{
	Spawned.RemoveAll([](const TWeakObjectPtr<AActor>& Product) { return !Product.IsValid(); });

	for (int32 Index = 0; Index < Spawned.Num() && Spawned.Num() >= MaxProducts;)
	{
		AActor* Product = Spawned[Index].Get();
		const UGrabbableComponent* Grabbable = Product->FindComponentByClass<UGrabbableComponent>();
		if (Product != CurrentProduct && !(Grabbable && Grabbable->IsHeld()))
		{
			Spawned.RemoveAt(Index);
			Product->Destroy();
		}
		else
		{
			++Index;
		}
	}
}

void AProductDispenser::SpawnProduct()
{
	if (!ProductClass || CurrentProduct)
	{
		return;
	}

	MakeRoom();

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FTransform SpawnTransform(SpawnPoint->GetComponentRotation(), SpawnPoint->GetComponentLocation());
	AActor* Product = GetWorld()->SpawnActor<AActor>(ProductClass, SpawnTransform, Params);
	if (!Product)
	{
		UE_LOG(LogTAKT, Warning, TEXT("%s: no se ha podido crear el producto."), *GetName());
		return;
	}

	if (UGrabbableComponent* Grabbable = Product->FindComponentByClass<UGrabbableComponent>())
	{
		Grabbable->OnGrabbed.AddDynamic(this, &AProductDispenser::HandleProductGrabbed);
	}
	else
	{
		UE_LOG(LogTAKT, Warning, TEXT("%s: %s no tiene «Cogible»; no se repondrá al cogerlo."),
			*GetName(), *GetNameSafe(ProductClass));
	}
	Product->OnDestroyed.AddDynamic(this, &AProductDispenser::HandleProductDestroyed);

	CurrentProduct = Product;
	Spawned.Add(Product);
}
