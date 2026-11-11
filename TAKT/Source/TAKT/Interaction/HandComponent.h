#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Templates/SubclassOf.h"
#include "HandComponent.generated.h"

class UGrabbableComponent;
class UInputAction;

/**
 * Mano del jugador: coge y suelta cogibles (ADR 0016).
 *
 * Va como hija del controlador de movimiento de cada mano en el pawn, así que se mueve con
 * el mando. Grab() coge el cogible más cercano dentro de GrabRadius y Release() lo suelta con
 * la velocidad de la mano, para poder lanzarlo. Si lo más cercano es un accionable (una
 * palanca), Grab() lo acciona en lugar de coger nada (ADR 0017).
 *
 * La entrada se elige con datos (Enhanced Input): GrabAction coge y ReleaseAction suelta, cada
 * una al dispararse (la plantilla VR las trae separadas: IA_Grab_*_Pressed e IA_Grab_*_Released).
 * Si no hay ReleaseAction, suelta cuando termina GrabAction (una acción sin triggers que dura
 * mientras se mantiene el botón). Cambiar de botón o de mando se hace en el Input Mapping
 * Context, sin tocar este código.
 */
UCLASS(ClassGroup = (TAKT), meta = (BlueprintSpawnableComponent, DisplayName = "Mano"))
class TAKT_API UHandComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UHandComponent();

	/**
	 * Coge el cogible más cercano o, si hay un accionable más cerca, lo acciona.
	 * Devuelve true solo si ha cogido algo.
	 */
	UFUNCTION(BlueprintCallable, Category = "TAKT|Interacción")
	bool Grab();

	/** Suelta lo que sostiene con la velocidad actual de la mano. */
	UFUNCTION(BlueprintCallable, Category = "TAKT|Interacción")
	void Release();

	/** Lo que sostiene, o nada. */
	UFUNCTION(BlueprintPure, Category = "TAKT|Interacción")
	UGrabbableComponent* GetHeld() const { return Held; }

	/** Velocidad de la mano en cm/s, suavizada. */
	UFUNCTION(BlueprintPure, Category = "TAKT|Interacción")
	FVector GetHandVelocity() const { return Velocity; }

	/** Lo llama un cogible cuando otra mano se lo quita a esta. */
	void NotifyTakenByOtherHand(const UGrabbableComponent* Grabbable);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Input Action que coge al dispararse (en la plantilla, IA_Grab_Left_Pressed o IA_Grab_Right_Pressed). */
	UPROPERTY(EditAnywhere, Category = "TAKT|Interacción")
	TObjectPtr<UInputAction> GrabAction;

	/** Input Action que suelta al dispararse (IA_Grab_*_Released). Vacía: suelta cuando termina GrabAction. */
	UPROPERTY(EditAnywhere, Category = "TAKT|Interacción")
	TObjectPtr<UInputAction> ReleaseAction;

	/** Distancia máxima, en cm, entre la mano y el cogible. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Interacción", meta = (ClampMin = "1.0", Units = "cm"))
	float GrabRadius = 15.f;

private:
	/** Engancha las acciones a la entrada del pawn en cuanto exista (llega después de BeginPlay). */
	void TryBindInput();

	void HandleGrabInput();
	void HandleReleaseInput();

	/** Componente de la clase indicada más cercano a la mano dentro de GrabRadius, y su distancia. */
	UActorComponent* FindNearest(TSubclassOf<UActorComponent> ComponentClass, float& OutDistance) const;

	UPROPERTY(Transient)
	TObjectPtr<UGrabbableComponent> Held;

	bool bInputBound = false;

	FVector PreviousLocation = FVector::ZeroVector;
	bool bHasPreviousLocation = false;
	FVector Velocity = FVector::ZeroVector;
};
