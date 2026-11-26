#include "Game/ScoreBoard.h"

#include "TAKT.h"

#include "Components/TextRenderComponent.h"
#include "Game/OutputBin.h"

AScoreBoard::AScoreBoard()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	Text->SetupAttachment(GetRootComponent());
	Text->SetHorizontalAlignment(EHTA_Center);
	Text->SetVerticalAlignment(EVRTA_TextCenter);
	Text->SetTextRenderColor(FColor::White);
	Text->SetWorldSize(TextSize);
	Text->SetText(FText::FromString(TEXT("Puntos: 0")));
}

void AScoreBoard::BeginPlay()
{
	Super::BeginPlay();

	Text->SetWorldSize(TextSize);

	if (!Bin)
	{
		UE_LOG(LogTAKT, Warning, TEXT("%s: no tiene ninguna caja de salida asignada."), *GetName());
	}
	else
	{
		Bin->OnPairDelivered.AddDynamic(this, &AScoreBoard::HandlePair);
		Bin->OnSingleDelivered.AddDynamic(this, &AScoreBoard::HandleSingle);
	}

	Refresh();
}

void AScoreBoard::ResetScore()
{
	Score = 0;
	Singles = 0;
	Refresh();
}

void AScoreBoard::HandlePair()
{
	Score += PointsPerPair;
	Refresh();
}

void AScoreBoard::HandleSingle()
{
	++Singles;
	Refresh();
}

void AScoreBoard::Refresh()
{
	Text->SetText(FText::FromString(FString::Printf(TEXT("Puntos: %d\nSueltos: %d"), Score, Singles)));
}
