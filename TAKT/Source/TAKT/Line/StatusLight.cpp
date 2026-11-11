#include "Line/StatusLight.h"

#include "TAKT.h"

#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

AStatusLight::AStatusLight()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ShapeMaterial(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	// Bola de 15 cm. Sin colisión ni sombra: es solo un indicador.
	Bulb = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bulb"));
	Bulb->SetupAttachment(GetRootComponent());
	Bulb->SetMobility(EComponentMobility::Movable);
	Bulb->SetStaticMesh(SphereMesh.Object);
	Bulb->SetMaterial(0, ShapeMaterial.Object);
	Bulb->SetRelativeScale3D(FVector(0.15f));
	Bulb->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Bulb->SetCastShadow(false);

	// Sin sombras para no añadir coste por Link (ADR 0015).
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(GetRootComponent());
	Light->SetMobility(EComponentMobility::Movable);
	Light->SetIntensityUnits(ELightUnits::Candelas);
	Light->SetIntensity(20.f);
	Light->SetAttenuationRadius(250.f);
	Light->SetCastShadows(false);
	Light->SetLightColor(StoppedColor);
}

void AStatusLight::BeginPlay()
{
	Super::BeginPlay();

	BulbMaterial = Bulb->CreateDynamicMaterialInstance(0);

	if (!Line)
	{
		UE_LOG(LogTAKT, Warning, TEXT("%s: no tiene ninguna línea asignada."), *GetName());
		return;
	}

	Line->OnStateChanged.AddDynamic(this, &AStatusLight::HandleStateChanged);

	// El control pone su estado inicial en su BeginPlay sin emitir OnStateChanged, y el orden
	// de BeginPlay entre actores no está garantizado: se mira en el siguiente tick.
	GetWorldTimerManager().SetTimerForNextTick(this, &AStatusLight::ApplyCurrentState);
}

void AStatusLight::HandleStateChanged(ELineState OldState, ELineState NewState)
{
	ApplyColor(GetColorFor(NewState));
}

void AStatusLight::ApplyCurrentState()
{
	if (Line)
	{
		ApplyColor(GetColorFor(Line->GetState()));
	}
}

void AStatusLight::ApplyColor(const FLinearColor& Color)
{
	Light->SetLightColor(Color);
	if (BulbMaterial)
	{
		BulbMaterial->SetVectorParameterValue(ColorParameterName, Color);
	}
}

FLinearColor AStatusLight::GetColorFor(ELineState State) const
{
	switch (State)
	{
	case ELineState::Running:
		return RunningColor;
	case ELineState::Faulted:
		return FaultedColor;
	case ELineState::Stopped:
	default:
		return StoppedColor;
	}
}
