#include "MediumTarget.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AngryGameMode.h"


AMediumTarget::AMediumTarget()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMediumTarget::BeginPlay()
{
	Super::BeginPlay();
}

int32 AMediumTarget::GetBaseScore() const
{
	return 20;
}

void AMediumTarget::IncrementScore()
{
	AAngryGameMode* GameMode = Cast<AAngryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->AddScore(GetBaseScore());
	}
}