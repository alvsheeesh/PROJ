#include "Line/LineController.h"

#include "TAKT.h"

#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Line/ConveyorBelt.h"
#include "TimerManager.h"

ALineController::ALineController()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
}

void ALineController::BeginPlay()
{
	Super::BeginPlay();

	if (Belts.IsEmpty())
	{
		UE_LOG(LogTAKT, Warning, TEXT("%s: no tiene ninguna cinta asignada."), *GetName());
	}

	State = bStartRunning ? ELineState::Running : ELineState::Stopped;

	// El orden de BeginPlay entre actores no está garantizado: si una cinta
	// empieza después que el control, se pondría según su propio bStartRunning.
	// Se aplica en el siguiente tick, cuando todas ya han empezado.
	GetWorldTimerManager().SetTimerForNextTick(this, &ALineController::ApplyToBelts);
}

bool ALineController::Start()
{
	return TryTransition(ELineState::Stopped, ELineState::Running);
}

bool ALineController::Stop()
{
	return TryTransition(ELineState::Running, ELineState::Stopped);
}

bool ALineController::TriggerFault()
{
	return TryTransition(ELineState::Running, ELineState::Faulted);
}

bool ALineController::Repair()
{
	return TryTransition(ELineState::Faulted, ELineState::Stopped);
}

bool ALineController::TryTransition(ELineState From, ELineState To)
{
	if (State != From)
	{
		UE_LOG(LogTAKT, Log, TEXT("%s: no se puede pasar a %s desde %s."), *GetName(),
			*UEnum::GetDisplayValueAsText(To).ToString(), *UEnum::GetDisplayValueAsText(State).ToString());
#if !UE_BUILD_SHIPPING
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Orange, FString::Printf(TEXT("Línea: no se puede pasar a %s desde %s"),
				*UEnum::GetDisplayValueAsText(To).ToString(), *UEnum::GetDisplayValueAsText(State).ToString()));
		}
#endif
		return false;
	}

	State = To;
	ApplyToBelts();

	UE_LOG(LogTAKT, Log, TEXT("%s: %s -> %s"), *GetName(),
		*UEnum::GetDisplayValueAsText(From).ToString(), *UEnum::GetDisplayValueAsText(To).ToString());
#if !UE_BUILD_SHIPPING
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, FString::Printf(TEXT("Línea: %s -> %s"),
			*UEnum::GetDisplayValueAsText(From).ToString(), *UEnum::GetDisplayValueAsText(To).ToString()));
	}
#endif
	OnStateChanged.Broadcast(From, To);
	return true;
}

void ALineController::ApplyToBelts()
{
	const bool bBeltsRunning = IsRunning();
	for (AConveyorBelt* Belt : Belts)
	{
		if (Belt)
		{
			Belt->SetRunning(bBeltsRunning);
		}
	}
}
