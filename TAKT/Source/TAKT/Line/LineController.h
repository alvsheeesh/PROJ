#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LineController.generated.h"

class AConveyorBelt;

/** Estado de la línea de manipulados (ADR 0014). */
UENUM(BlueprintType)
enum class ELineState : uint8
{
	Stopped UMETA(DisplayName = "Parada"),
	Running UMETA(DisplayName = "En marcha"),
	Faulted UMETA(DisplayName = "Averiada"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLineStateChanged, ELineState, OldState, ELineState, NewState);

/**
 * Control de una línea de manipulados: es el dueño de su estado (ADR 0014).
 *
 * Transiciones:
 *   Parada  -> En marcha  Start (el botón verde)
 *   En marcha -> Parada   Stop
 *   En marcha -> Averiada TriggerFault (las cintas se paran)
 *   Averiada -> Parada    Repair (luego hay que volver a pulsar Start)
 * Cualquier otra llamada no hace nada y devuelve false.
 *
 * Modelo mixto: las cintas de la línea son suyas y les manda SetRunning
 * directamente; todo lo demás (luz, botones, sonido) se entera escuchando
 * OnStateChanged, sin que el control lo conozca.
 */
UCLASS(Blueprintable, ClassGroup = (TAKT), meta = (DisplayName = "Control de línea"))
class TAKT_API ALineController : public AActor
{
	GENERATED_BODY()

public:
	ALineController();

	/** Se emite en cada cambio de estado, después de aplicarlo a las cintas. */
	UPROPERTY(BlueprintAssignable, Category = "TAKT|Línea")
	FOnLineStateChanged OnStateChanged;

	UFUNCTION(BlueprintPure, Category = "TAKT|Línea")
	ELineState GetState() const { return State; }

	UFUNCTION(BlueprintPure, Category = "TAKT|Línea")
	bool IsRunning() const { return State == ELineState::Running; }

	/** Parada -> En marcha. */
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "TAKT|Línea")
	bool Start();

	/** En marcha -> Parada. */
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "TAKT|Línea")
	bool Stop();

	/** En marcha -> Averiada. */
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "TAKT|Línea")
	bool TriggerFault();

	/** Averiada -> Parada. */
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "TAKT|Línea")
	bool Repair();

protected:
	virtual void BeginPlay() override;

	/** Cintas que manda este control. Se eligen en el nivel. */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "TAKT|Línea")
	TArray<TObjectPtr<AConveyorBelt>> Belts;

	/** Si la línea empieza en marcha. Si no, empieza parada y espera a Start. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Línea")
	bool bStartRunning = true;

private:
	/** Cambia de From a To si el estado actual es From. */
	bool TryTransition(ELineState From, ELineState To);

	/** Pone las cintas en marcha o paradas según el estado actual. */
	void ApplyToBelts();

	ELineState State = ELineState::Stopped;
};
