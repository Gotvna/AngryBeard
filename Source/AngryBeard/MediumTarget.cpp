#include "MediumTarget.h"
#include "Kismet/GameplayStatics.h"
#include "AngryGameMode.h"

void AMediumTarget::IncrementScore()
{
	AAngryGameMode* GameMode = Cast<AAngryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->AddScore(2);
	}
}
