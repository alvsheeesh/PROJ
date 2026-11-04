#include "Interaction/HandComponent.h"

#include "TAKT.h"

#include "CollisionQueryParams.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/Engine.h"
#include "Engine/OverlapResult.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "Interaction/GrabbableComponent.h"

namespace
{
	/** Peso de la última medida en la velocidad suavizada de la mano. */
	constexpr float VelocitySmoothing = 0.5f;
}

UHandComponent::UHandComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	// Después de que el controlador de movimiento actualice la posición del mando.
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
}

void UHandComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!GrabAction)
	{
		UE_LOG(LogTAKT, Warning, TEXT("%s (%s): no tiene Grab Action; solo responde a Grab() y Release()."),
			*GetName(), *GetNameSafe(GetOwner()));
	}
}

void UHandComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TryBindInput();

	const FVector Location = GetComponentLocation();
	if (bHasPreviousLocation && DeltaTime > UE_KINDA_SMALL_NUMBER)
	{
		const FVector Measured = (Location - PreviousLocation) / DeltaTime;
		Velocity = FMath::Lerp(Velocity, Measured, VelocitySmoothing);
	}
	PreviousLocation = Location;
	bHasPreviousLocation = true;
}

void UHandComponent::TryBindInput()
{
	if (bInputBound || !GrabAction)
	{
		return;
	}

	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn || !Pawn->IsLocallyControlled())
	{
		return;
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(Pawn->InputComponent);
	if (!Input)
	{
		return;
	}

	// Triggered y no Started: con el trigger Pressed de la plantilla, la acción empieza y termina
	// en el mismo gesto, y soltar al terminar soltaba el objeto en el fotograma siguiente.
	Input->BindAction(GrabAction, ETriggerEvent::Triggered, this, &UHandComponent::HandleGrabInput);
	if (ReleaseAction)
	{
		Input->BindAction(ReleaseAction, ETriggerEvent::Triggered, this, &UHandComponent::HandleReleaseInput);
	}
	else
	{
		Input->BindAction(GrabAction, ETriggerEvent::Completed, this, &UHandComponent::HandleReleaseInput);
	}
	bInputBound = true;

	UE_LOG(LogTAKT, Log, TEXT("%s: coge con %s y suelta con %s."), *GetName(), *GrabAction->GetName(),
		ReleaseAction ? *ReleaseAction->GetName() : TEXT("el final de la misma acción"));
}

void UHandComponent::HandleGrabInput()
{
	Grab();
}

void UHandComponent::HandleReleaseInput()
{
	Release();
}

bool UHandComponent::Grab()
{
	if (Held)
	{
		return true;
	}

	UGrabbableComponent* Nearest = FindNearestGrabbable();
	if (!Nearest)
	{
		UE_LOG(LogTAKT, Verbose, TEXT("%s: nada que coger a %.0f cm."), *GetName(), GrabRadius);
		return false;
	}

	if (!Nearest->BeginGrab(this))
	{
		return false;
	}

	Held = Nearest;
	return true;
}

void UHandComponent::Release()
{
	if (!Held)
	{
		return;
	}

	UGrabbableComponent* Grabbable = Held;
	Held = nullptr;
	Grabbable->EndGrab(Velocity);
}

void UHandComponent::NotifyTakenByOtherHand(const UGrabbableComponent* Grabbable)
{
	if (Held == Grabbable)
	{
		Held = nullptr;
	}
}

UGrabbableComponent* UHandComponent::FindNearestGrabbable() const
{
	const UWorld* World = GetWorld();
	if (!World)
	{
		return nullptr;
	}

	const FVector HandLocation = GetComponentLocation();

	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(TAKTHandGrab), false, GetOwner());
	World->OverlapMultiByObjectType(Overlaps, HandLocation, FQuat::Identity,
		FCollisionObjectQueryParams(FCollisionObjectQueryParams::AllDynamicObjects),
		FCollisionShape::MakeSphere(GrabRadius), Params);

	UGrabbableComponent* Nearest = nullptr;
	float NearestDistance = TNumericLimits<float>::Max();
	for (const FOverlapResult& Overlap : Overlaps)
	{
		const AActor* Actor = Overlap.GetActor();
		UPrimitiveComponent* Primitive = Overlap.GetComponent();
		if (!Actor || !Primitive)
		{
			continue;
		}

		UGrabbableComponent* Grabbable = Actor->FindComponentByClass<UGrabbableComponent>();
		if (!Grabbable)
		{
			continue;
		}

		// Distancia a la superficie del objeto; si no se puede calcular, a su centro.
		FVector ClosestPoint;
		float Distance = Primitive->GetClosestPointOnCollision(HandLocation, ClosestPoint);
		if (Distance < 0.f)
		{
			Distance = FVector::Dist(HandLocation, Primitive->GetComponentLocation());
		}

		if (Distance < NearestDistance)
		{
			NearestDistance = Distance;
			Nearest = Grabbable;
		}
	}
	return Nearest;
}
