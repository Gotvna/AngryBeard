#include "LargeTarget.h"
#include "Kismet/GameplayStatics.h"
#include "AngryGameMode.h"

int32 ALargeTarget::GetBaseScore() const
{
	return 50;
}

void ALargeTarget::IncrementScore()
{
	AAngryGameMode* GameMode = Cast<AAngryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->AddScore(GetBaseScore());
	}
}
