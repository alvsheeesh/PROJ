#include "Line/RandomFaultComponent.h"

#include "TAKT.h"

#include "Engine/World.h"
#include "TimerManager.h"

URandomFaultComponent::URandomFaultComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URandomFaultComponent::BeginPlay()
{
	Super::BeginPlay();

	Line = Cast<ALineController>(GetOwner());
	if (!Line)
	{
		UE_LOG(LogTAKT, Warning, TEXT("%s: tiene que ir en un control de línea (está en %s)."),
			*GetName(), *GetNameSafe(GetOwner()));
		return;
	}

	Line->OnStateChanged.AddDynamic(this, &URandomFaultComponent::HandleStateChanged);

	// El control pone su estado inicial en su BeginPlay, después que el de sus componentes,
	// y sin emitir OnStateChanged: se mira en el siguiente tick.
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &URandomFaultComponent::ScheduleIfRunning);
}

void URandomFaultComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(FaultTimer);
	}
	Super::EndPlay(EndPlayReason);
}

float URandomFaultComponent::GetTimeToFault() const
{
	const UWorld* World = GetWorld();
	return World ? World->GetTimerManager().GetTimerRemaining(FaultTimer) : -1.f;
}

void URandomFaultComponent::HandleStateChanged(ELineState OldState, ELineState NewState)
{
	GetWorld()->GetTimerManager().ClearTimer(FaultTimer);
	ScheduleIfRunning();
}

void URandomFaultComponent::ScheduleIfRunning()
{
	if (!bFaultsEnabled || !Line || !Line->IsRunning())
	{
		return;
	}

	const float Delay = FMath::FRandRange(MinDelay, FMath::Max(MinDelay, MaxDelay));
	GetWorld()->GetTimerManager().SetTimer(FaultTimer, this, &URandomFaultComponent::FireFault, Delay, false);
	UE_LOG(LogTAKT, Log, TEXT("%s: atasco dentro de %.1f s."), *GetNameSafe(Line), Delay);
}

void URandomFaultComponent::FireFault()
{
	if (Line)
	{
		UE_LOG(LogTAKT, Log, TEXT("%s: atasco."), *GetNameSafe(Line));
		Line->TriggerFault();
	}
}
