#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Line/LineController.h"
#include "RandomFaultComponent.generated.h"

/**
 * Provoca el atasco de una línea al cabo de un tiempo aleatorio (ADR 0017).
 *
 * Se añade al control de línea. Cada vez que la línea pasa a En marcha, elige una espera entre
 * MinDelay y MaxDelay segundos y, al acabar, llama a TriggerFault. Si la línea deja de estar en
 * marcha antes (Stop o una avería provocada desde otro sitio), cancela la espera.
 *
 * El control no sabe que existe: otra causa de avería (por ejemplo, detectar objetos atascados
 * en la cinta) sería otro componente que también llame a TriggerFault.
 */
UCLASS(ClassGroup = (TAKT), meta = (BlueprintSpawnableComponent, DisplayName = "Averías aleatorias"))
class TAKT_API URandomFaultComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URandomFaultComponent();

	/** Segundos que faltan para la próxima avería, o -1 si no hay ninguna programada. */
	UFUNCTION(BlueprintPure, Category = "TAKT|Avería")
	float GetTimeToFault() const;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Si está desactivado, no provoca averías (se pueden seguir provocando con TriggerFault). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Avería")
	bool bFaultsEnabled = true;

	/** Espera mínima, en segundos de línea en marcha, antes del atasco. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Avería", meta = (ClampMin = "1.0", Units = "s"))
	float MinDelay = 20.f;

	/** Espera máxima. Si es menor que la mínima, se usa la mínima. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Avería", meta = (ClampMin = "1.0", Units = "s"))
	float MaxDelay = 45.f;

private:
	UFUNCTION()
	void HandleStateChanged(ELineState OldState, ELineState NewState);

	/** Programa la avería si la línea está en marcha. */
	void ScheduleIfRunning();

	void FireFault();

	UPROPERTY(Transient)
	TObjectPtr<ALineController> Line;

	FTimerHandle FaultTimer;
};
