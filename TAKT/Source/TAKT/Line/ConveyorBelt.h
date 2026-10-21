#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConveyorBelt.generated.h"

class UArrowComponent;
class UBoxComponent;
class UPhysicalMaterial;
class UStaticMeshComponent;

/**
 * Tramo recto de cinta transportadora (ADR 0012).
 *
 * Mueve por física lo que tiene encima: cada tick busca los cuerpos que simulan
 * física dentro de la zona de transporte y lleva su velocidad horizontal hacia
 * la de la cinta. Lo que el jugador tiene cogido no simula física mientras lo
 * sujeta, así que la cinta no lo toca.
 *
 * La cinta no decide cuándo pararse: obedece a SetRunning, que llamará el estado
 * de la máquina (TAKT-25). Parada, frena lo que lleva encima.
 *
 * El origen del actor es el centro de la superficie y la cinta avanza hacia su
 * X local (la flecha amarilla). Solo cintas horizontales.
 */
UCLASS(Blueprintable, ClassGroup = (TAKT), meta = (DisplayName = "Cinta transportadora"))
class TAKT_API AConveyorBelt : public AActor
{
	GENERATED_BODY()

public:
	AConveyorBelt();

	/** Pone en marcha (true) o para (false) la cinta. */
	UFUNCTION(BlueprintCallable, Category = "TAKT|Cinta")
	void SetRunning(bool bInRunning);

	UFUNCTION(BlueprintPure, Category = "TAKT|Cinta")
	bool IsRunning() const { return bRunning; }

	/** Velocidad de avance en marcha, en cm/s. */
	UFUNCTION(BlueprintPure, Category = "TAKT|Cinta")
	float GetSpeed() const { return Speed; }

	/** Botón de depuración del panel de detalles: con la partida en marcha, para o arranca la cinta. */
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "TAKT|Cinta")
	void ToggleRunning();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Velocidad de avance en marcha. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Cinta", meta = (ClampMin = "0.0", Units = "CentimetersPerSecond"))
	float Speed = 40.f;

	/** Si la cinta empieza en marcha al empezar la partida. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Cinta")
	bool bStartRunning = true;

	/**
	 * Rapidez con la que los objetos toman la velocidad de la cinta, en 1/s.
	 * Con 15, un objeto que cae encima va a la velocidad de la cinta en unos 0,2 s.
	 */
	UPROPERTY(EditAnywhere, Category = "TAKT|Cinta", AdvancedDisplay, meta = (ClampMin = "0.1"))
	float Grip = 15.f;

	/** Largo (X) y ancho (Y) de la superficie. */
	UPROPERTY(EditAnywhere, Category = "TAKT|Cinta|Forma", meta = (ClampMin = "10.0", Units = "Centimeters"))
	FVector2D BeltSize = FVector2D(200.f, 50.f);

	/** Grosor de la cinta, por debajo de la superficie. */
	UPROPERTY(EditAnywhere, Category = "TAKT|Cinta|Forma", meta = (ClampMin = "1.0", Units = "Centimeters"))
	float Thickness = 10.f;

	/** Altura de la zona de transporte por encima de la superficie. */
	UPROPERTY(EditAnywhere, Category = "TAKT|Cinta|Forma", AdvancedDisplay, meta = (ClampMin = "1.0", Units = "Centimeters"))
	float CarryHeight = 15.f;

	/**
	 * Material físico de la superficie. Si se deja vacío, se crea uno sin fricción al empezar:
	 * la velocidad de lo que va encima la controla la cinta, no el rozamiento.
	 */
	UPROPERTY(EditAnywhere, Category = "TAKT|Cinta", AdvancedDisplay)
	TObjectPtr<UPhysicalMaterial> SurfaceMaterial;

	/** Dibuja la zona de transporte (verde en marcha, roja parada) y lo que lleva encima. */
	UPROPERTY(EditAnywhere, Category = "TAKT|Cinta|Depuración")
	bool bDrawDebug = false;

	UPROPERTY(VisibleAnywhere, Category = "Componentes")
	TObjectPtr<USceneComponent> Root;

	/** Cuerpo de la cinta: el cubo básico del motor, escalado según BeltSize y Thickness. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes")
	TObjectPtr<UStaticMeshComponent> BeltMesh;

	/** Volumen donde la cinta arrastra los objetos. Solo marca la zona: no tiene colisión. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes")
	TObjectPtr<UBoxComponent> CarryZone;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UArrowComponent> DirectionArrow;
#endif

private:
	/** Ajusta la malla y la zona de transporte a BeltSize, Thickness y CarryHeight. */
	void UpdateLayout();

	/** Lleva la velocidad horizontal de los cuerpos de la zona hacia la de la cinta. */
	void CarryBodies(float DeltaSeconds);

	bool bRunning = false;
};
