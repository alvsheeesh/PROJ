#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProductDispenser.generated.h"

class UHandComponent;
class UStaticMeshComponent;

/**
 * Bandeja que nunca se vacía (ADR 0018).
 *
 * Tiene siempre un producto encima. Cuando una mano lo coge («Cogible», OnGrabbed), deja de
 * vigilarlo y pone otro al cabo de RefillDelay segundos. Para no cargar la física, si ya hay
 * MaxProducts productos suyos en el nivel, elimina el más antiguo que nadie sostiene.
 *
 * Prueba sin gafas: `ke * Dispense` hace como si se hubiera cogido el producto.
 */
UCLASS(ClassGroup = (TAKT), meta = (DisplayName = "Dispensador"))
class TAKT_API AProductDispenser : public AActor
{
	GENERATED_BODY()

public:
	AProductDispenser();

	/** Da por cogido el producto de la bandeja y prepara otro. */
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "TAKT|Dispensador")
	void Dispense();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Lo que pone en la bandeja. Tiene que llevar un «Cogible». */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Dispensador")
	TSubclassOf<AActor> ProductClass;

	/** Segundos entre que se coge un producto y aparece el siguiente. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Dispensador", meta = (ClampMin = "0.0", Units = "s"))
	float RefillDelay = 0.5f;

	/** Productos suyos que puede haber a la vez en el nivel. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Dispensador", meta = (ClampMin = "2"))
	int32 MaxProducts = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TAKT|Dispensador")
	TObjectPtr<UStaticMeshComponent> Tray;

	/** Donde aparece el producto: un poco por encima de la bandeja. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TAKT|Dispensador")
	TObjectPtr<USceneComponent> SpawnPoint;

private:
	UFUNCTION()
	void HandleProductGrabbed(UHandComponent* Hand);

	UFUNCTION()
	void HandleProductDestroyed(AActor* DestroyedActor);

	void SpawnProduct();
	void ScheduleRefill();

	/** Deja de vigilar el producto de la bandeja: ya es del jugador. */
	void ReleaseCurrent();

	/** Elimina los productos más antiguos hasta dejar sitio para uno nuevo. */
	void MakeRoom();

	UPROPERTY(Transient)
	TObjectPtr<AActor> CurrentProduct;

	TArray<TWeakObjectPtr<AActor>> Spawned;

	FTimerHandle RefillTimer;
};
