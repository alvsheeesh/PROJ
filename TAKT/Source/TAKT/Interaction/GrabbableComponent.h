#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabbableComponent.generated.h"

class UHandComponent;
class UPrimitiveComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGrabbableHandEvent, UHandComponent*, Hand);

/**
 * Hace que su actor se pueda coger con una mano (ADR 0016).
 *
 * Mueve el componente con física del actor (su raíz, o si no el primero que simule física):
 * al cogerlo apaga su física y lo engancha a la mano; al soltarlo le devuelve la física con
 * la velocidad que llevaba la mano. No sabe nada de mandos ni de botones: lo usa
 * UHandComponent, y el resto del juego se entera escuchando OnGrabbed y OnReleased.
 */
UCLASS(ClassGroup = (TAKT), meta = (BlueprintSpawnableComponent, DisplayName = "Cogible"))
class TAKT_API UGrabbableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGrabbableComponent();

	/** Se emite cuando una mano lo coge, ya enganchado a ella. */
	UPROPERTY(BlueprintAssignable, Category = "TAKT|Interacción")
	FOnGrabbableHandEvent OnGrabbed;

	/** Se emite cuando la mano lo suelta, con la física ya devuelta. */
	UPROPERTY(BlueprintAssignable, Category = "TAKT|Interacción")
	FOnGrabbableHandEvent OnReleased;

	UFUNCTION(BlueprintPure, Category = "TAKT|Interacción")
	bool IsHeld() const { return Holder != nullptr; }

	/** Mano que lo sostiene, o ninguna. */
	UFUNCTION(BlueprintPure, Category = "TAKT|Interacción")
	UHandComponent* GetHolder() const { return Holder; }

	/** Componente que se engancha a la mano: la raíz si es un primitivo, o el primero con física. */
	UPrimitiveComponent* GetGrabbedPrimitive() const;

	/** Lo llama la mano al coger. Si lo tenía otra mano, se lo quita. Devuelve false si no se puede coger. */
	bool BeginGrab(UHandComponent* Hand);

	/** Lo llama la mano que lo sostiene al soltarlo. */
	void EndGrab(const FVector& LinearVelocity);

private:
	UPROPERTY(Transient)
	TObjectPtr<UHandComponent> Holder;

	/** Si simulaba física antes de cogerlo: al soltarlo se deja igual. */
	bool bWasSimulatingPhysics = false;
};
