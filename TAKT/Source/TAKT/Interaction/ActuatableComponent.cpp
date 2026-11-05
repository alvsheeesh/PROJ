#include "Interaction/ActuatableComponent.h"

#include "TAKT.h"

#include "Engine/World.h"
#include "Interaction/HandComponent.h"

UActuatableComponent::UActuatableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UActuatableComponent::Actuate(UHandComponent* Hand)
{
	const UWorld* World = GetWorld();
	const double Now = World ? World->GetTimeSeconds() : 0.0;
	if (Now - LastActuationTime < Cooldown)
	{
		return false;
	}
	LastActuationTime = Now;

	UE_LOG(LogTAKT, Log, TEXT("%s: accionado por %s."), *GetNameSafe(GetOwner()),
		Hand ? *Hand->GetName() : TEXT("la consola"));
	OnActuated.Broadcast(Hand);
	return true;
}
