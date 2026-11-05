#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lever.generated.h"

class ALineController;
class UActuatableComponent;
class UHandComponent;
class UStaticMeshComponent;

/**
 * Palanca de reparación de una línea (ADR 0017).
 *
 * Lleva un «Accionable»: al accionarla, si la línea está averiada la repara (Repair) y, si
 * bStartAfterRepair, la vuelve a arrancar (Start). En cualquier otro estado solo se mueve.
 * El mango baja hasta PulledAngle y vuelve, como respuesta visual.
 *
 * Prueba sin gafas: `ke * TriggerFault` y después `ke * Actuate`.
 */
UCLASS(ClassGroup = (TAKT), meta = (DisplayName = "Palanca"))
class TAKT_API ALever : public AActor
{
	GENERATED_BODY()

public:
	ALever();

	/** Acciona la palanca como si lo hiciera una mano. */
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "TAKT|Palanca")
	void Actuate();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Línea que repara. Se elige en el nivel. */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "TAKT|Palanca")
	TObjectPtr<ALineController> Line;

	/** Si después de reparar vuelve a arrancar la línea. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Palanca")
	bool bStartAfterRepair = true;

	/** Ángulo, en grados, al que baja el mango al accionarla. */
	UPROPERTY(EditAnywhere, Category = "TAKT|Palanca", meta = (Units = "deg"))
	float PulledAngle = -60.f;

	/** Duración, en segundos, de bajar y volver a subir el mango. */
	UPROPERTY(EditAnywhere, Category = "TAKT|Palanca", meta = (ClampMin = "0.05", Units = "s"))
	float AnimationDuration = 0.6f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TAKT|Palanca")
	TObjectPtr<UStaticMeshComponent> Base;

	/** Eje de giro del mango. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TAKT|Palanca")
	TObjectPtr<USceneComponent> Pivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TAKT|Palanca")
	TObjectPtr<UStaticMeshComponent> Handle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TAKT|Palanca")
	TObjectPtr<UStaticMeshComponent> Knob;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TAKT|Palanca")
	TObjectPtr<UActuatableComponent> Actuatable;

private:
	UFUNCTION()
	void HandleActuated(UHandComponent* Hand);

	/** Tiempo de la animación del mango; negativo si no se está moviendo. */
	float AnimationTime = -1.f;
};
