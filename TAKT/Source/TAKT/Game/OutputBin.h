#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OutputBin.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutputBinEvent);

/**
 * Caja al final de la cinta que recoge los productos (ADR 0018).
 *
 * Cada producto que cae dentro (un actor con «Cogible» que nadie sostiene) se cuenta una
 * vez y desaparece al poco. Si llega otro antes de PairWindow segundos, los dos forman una
 * pareja (OnPairDelivered); si no, el primero ha llegado solo (OnSingleDelivered).
 * La caja no sabe de puntos: quien los lleve escucha estos eventos.
 *
 * Usa una consulta de solapamiento, como la cinta: no depende de «Generate Overlap Events».
 * El origen del actor es el centro del fondo de la caja.
 */
UCLASS(ClassGroup = (TAKT), meta = (DisplayName = "Caja de salida"))
class TAKT_API AOutputBin : public AActor
{
	GENERATED_BODY()

public:
	AOutputBin();

	/** Han llegado dos productos juntos. */
	UPROPERTY(BlueprintAssignable, Category = "TAKT|Caja")
	FOnOutputBinEvent OnPairDelivered;

	/** Ha llegado un producto solo. */
	UPROPERTY(BlueprintAssignable, Category = "TAKT|Caja")
	FOnOutputBinEvent OnSingleDelivered;

	UFUNCTION(BlueprintPure, Category = "TAKT|Caja")
	int32 GetPairs() const { return Pairs; }

	UFUNCTION(BlueprintPure, Category = "TAKT|Caja")
	int32 GetSingles() const { return Singles; }

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

	/**
	 * Tiempo máximo entre dos productos para que cuenten como pareja.
	 * Con la cinta a 40 cm/s, 0,75 s son unos 30 cm de separación.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Caja", meta = (ClampMin = "0.05", Units = "s"))
	float PairWindow = 0.75f;

	/** Segundos que se ve el producto dentro de la caja antes de desaparecer. */
	UPROPERTY(EditAnywhere, Category = "TAKT|Caja", meta = (ClampMin = "0.0", Units = "s"))
	float RemoveDelay = 0.5f;

	/** Largo (X), ancho (Y) y alto (Z) de la caja. */
	UPROPERTY(EditAnywhere, Category = "TAKT|Caja", meta = (Units = "Centimeters"))
	FVector BinSize = FVector(40.f, 60.f, 25.f);

	UPROPERTY(VisibleAnywhere, Category = "TAKT|Caja")
	TObjectPtr<UStaticMeshComponent> Bottom;

	UPROPERTY(VisibleAnywhere, Category = "TAKT|Caja")
	TObjectPtr<UStaticMeshComponent> WallFront;

	UPROPERTY(VisibleAnywhere, Category = "TAKT|Caja")
	TObjectPtr<UStaticMeshComponent> WallBack;

	UPROPERTY(VisibleAnywhere, Category = "TAKT|Caja")
	TObjectPtr<UStaticMeshComponent> WallLeft;

	UPROPERTY(VisibleAnywhere, Category = "TAKT|Caja")
	TObjectPtr<UStaticMeshComponent> WallRight;

	/** Zona donde se detectan los productos: el interior de la caja. */
	UPROPERTY(VisibleAnywhere, Category = "TAKT|Caja")
	TObjectPtr<UBoxComponent> Zone;

private:
	void Deliver(AActor* Product);
	void ExpirePending();

	UStaticMeshComponent* CreatePart(const FName Name);

	/** Productos ya contados, para no contarlos dos veces. */
	TArray<TWeakObjectPtr<AActor>> Counted;

	FTimerHandle PendingTimer;

	int32 Pairs = 0;
	int32 Singles = 0;
};
