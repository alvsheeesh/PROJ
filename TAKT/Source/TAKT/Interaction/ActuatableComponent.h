#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActuatableComponent.generated.h"

class UHandComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActuatableHandEvent, UHandComponent*, Hand);

/**
 * Hace que su actor se pueda accionar con una mano: el evento genérico «accionar» (ADR 0017).
 *
 * Es el hermano de UGrabbableComponent para lo que no se coge (una palanca, un botón): la mano
 * lo acciona con el mismo gesto de coger cuando no tiene un cogible más cerca. No sabe nada de
 * mandos ni de lo que pasa al accionarlo; quien lo usa escucha OnActuated.
 *
 * Se llama «Actuate» y no «Activate» porque UActorComponent ya tiene Activate e IsActive, que
 * son otra cosa (encender y apagar el componente).
 */
UCLASS(ClassGroup = (TAKT), meta = (BlueprintSpawnableComponent, DisplayName = "Accionable"))
class TAKT_API UActuatableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActuatableComponent();

	/** Se emite al accionarlo. Hand es la mano que lo ha accionado, o ninguna (desde la consola o el código). */
	UPROPERTY(BlueprintAssignable, Category = "TAKT|Interacción")
	FOnActuatableHandEvent OnActuated;

	/** Lo acciona. Devuelve false si se ha accionado hace menos de Cooldown. */
	UFUNCTION(BlueprintCallable, Category = "TAKT|Interacción")
	bool Actuate(UHandComponent* Hand);

protected:
	/** Tiempo mínimo, en segundos, entre dos accionamientos (evita repetirlo con un mismo gesto). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Interacción", meta = (ClampMin = "0.0", Units = "s"))
	float Cooldown = 0.5f;

private:
	double LastActuationTime = -1.0e9;
};
