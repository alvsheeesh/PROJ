#include "Interaction/GrabbableComponent.h"

#include "TAKT.h"

#include "Components/PrimitiveComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "Interaction/HandComponent.h"

namespace
{
	void ShowGrabDebug(const FString& Text, const FColor& Color)
	{
#if !UE_BUILD_SHIPPING
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, Color, Text);
		}
#endif
	}
}

UGrabbableComponent::UGrabbableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UPrimitiveComponent* UGrabbableComponent::GetGrabbedPrimitive() const
{
	const AActor* Owner = GetOwner();
	if (!Owner)
	{
		return nullptr;
	}

	if (UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(Owner->GetRootComponent()))
	{
		return Root;
	}

	TArray<UPrimitiveComponent*> Primitives;
	Owner->GetComponents(Primitives);
	for (UPrimitiveComponent* Primitive : Primitives)
	{
		if (Primitive->IsSimulatingPhysics())
		{
			return Primitive;
		}
	}
	return nullptr;
}

bool UGrabbableComponent::BeginGrab(UHandComponent* Hand)
{
	if (!Hand)
	{
		return false;
	}
	if (Holder == Hand)
	{
		return true;
	}

	UPrimitiveComponent* Primitive = GetGrabbedPrimitive();
	if (!Primitive)
	{
		UE_LOG(LogTAKT, Warning, TEXT("%s: no tiene ningún componente con física que coger."), *GetNameSafe(GetOwner()));
		return false;
	}

	if (Holder)
	{
		// Pasa de una mano a otra: la anterior lo pierde sin soltarlo.
		Holder->NotifyTakenByOtherHand(this);
	}
	else
	{
		bWasSimulatingPhysics = Primitive->IsSimulatingPhysics();
	}

	Primitive->SetSimulatePhysics(false);
	Primitive->AttachToComponent(Hand, FAttachmentTransformRules::KeepWorldTransform);
	Holder = Hand;

	UE_LOG(LogTAKT, Log, TEXT("%s: cogido por %s."), *GetNameSafe(GetOwner()), *Hand->GetName());
	ShowGrabDebug(FString::Printf(TEXT("Cogido: %s"), *GetNameSafe(GetOwner())), FColor::Cyan);
	OnGrabbed.Broadcast(Hand);
	return true;
}

void UGrabbableComponent::EndGrab(const FVector& LinearVelocity)
{
	UHandComponent* PreviousHolder = Holder;
	Holder = nullptr;

	if (UPrimitiveComponent* Primitive = GetGrabbedPrimitive())
	{
		Primitive->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		if (bWasSimulatingPhysics)
		{
			Primitive->SetSimulatePhysics(true);
			Primitive->SetPhysicsLinearVelocity(LinearVelocity);
		}
	}

	UE_LOG(LogTAKT, Log, TEXT("%s: soltado a %.0f cm/s."), *GetNameSafe(GetOwner()), LinearVelocity.Size());
	ShowGrabDebug(FString::Printf(TEXT("Soltado: %s"), *GetNameSafe(GetOwner())), FColor::Cyan);
	OnReleased.Broadcast(PreviousHolder);
}
