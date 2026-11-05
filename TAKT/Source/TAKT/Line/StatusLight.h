#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Line/LineController.h"
#include "StatusLight.generated.h"

class UMaterialInstanceDynamic;
class UPointLightComponent;
class UStaticMeshComponent;

/**
 * Luz que enseña el estado de una línea con un color (ADR 0017).
 *
 * Escucha OnStateChanged del control (ADR 0014): el control no sabe que existe. El color de
 * cada estado se cambia en Detalles. Pinta la bola con el parámetro de color de su material
 * (ColorParameterName) y le da el mismo color a la luz puntual.
 *
 * Prueba sin gafas: `ke * Stop`, `ke * Start` y `ke * TriggerFault`.
 */
UCLASS(ClassGroup = (TAKT), meta = (DisplayName = "Luz de estado"))
class TAKT_API AStatusLight : public AActor
{
	GENERATED_BODY()

public:
	AStatusLight();

protected:
	virtual void BeginPlay() override;

	/** Línea cuyo estado enseña. Se elige en el nivel. */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "TAKT|Luz")
	TObjectPtr<ALineController> Line;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Luz")
	FLinearColor RunningColor = FLinearColor(0.05f, 1.f, 0.1f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Luz")
	FLinearColor StoppedColor = FLinearColor(1.f, 0.55f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Luz")
	FLinearColor FaultedColor = FLinearColor(1.f, 0.02f, 0.02f);

	/** Parámetro de color del material de la bola (el material de las formas básicas usa «Color»). */
	UPROPERTY(EditAnywhere, Category = "TAKT|Luz")
	FName ColorParameterName = TEXT("Color");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TAKT|Luz")
	TObjectPtr<UStaticMeshComponent> Bulb;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TAKT|Luz")
	TObjectPtr<UPointLightComponent> Light;

private:
	UFUNCTION()
	void HandleStateChanged(ELineState OldState, ELineState NewState);

	/** Pone el color del estado actual de la línea. */
	void ApplyCurrentState();

	void ApplyColor(const FLinearColor& Color);

	FLinearColor GetColorFor(ELineState State) const;

	UPROPERTY(Transient)
	TObjectPtr<UMaterialInstanceDynamic> BulbMaterial;
};
