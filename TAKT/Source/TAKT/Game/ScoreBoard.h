#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreBoard.generated.h"

class AOutputBin;
class UTextRenderComponent;

/**
 * Marcador de la partida (ADR 0018).
 *
 * Escucha a la caja de salida: suma PointsPerPair por cada pareja y cuenta los productos que
 * llegan solos. Lo enseña con un texto 3D, que se lee mirando hacia la flecha del actor
 * (si sale al revés, girarlo 180° en Z).
 */
UCLASS(ClassGroup = (TAKT), meta = (DisplayName = "Marcador"))
class TAKT_API AScoreBoard : public AActor
{
	GENERATED_BODY()

public:
	AScoreBoard();

	/** Vuelve a cero. */
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "TAKT|Marcador")
	void ResetScore();

	UFUNCTION(BlueprintPure, Category = "TAKT|Marcador")
	int32 GetScore() const { return Score; }

protected:
	virtual void BeginPlay() override;

	/** Caja de salida que cuenta. Se elige en el nivel. */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "TAKT|Marcador")
	TObjectPtr<AOutputBin> Bin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TAKT|Marcador", meta = (ClampMin = "1"))
	int32 PointsPerPair = 10;

	/** Alto de las letras. */
	UPROPERTY(EditAnywhere, Category = "TAKT|Marcador", meta = (ClampMin = "1.0", Units = "Centimeters"))
	float TextSize = 8.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TAKT|Marcador")
	TObjectPtr<UTextRenderComponent> Text;

private:
	UFUNCTION()
	void HandlePair();

	UFUNCTION()
	void HandleSingle();

	void Refresh();

	int32 Score = 0;
	int32 Singles = 0;
};
