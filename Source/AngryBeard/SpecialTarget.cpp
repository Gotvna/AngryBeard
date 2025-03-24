#include "SpecialTarget.h"
#include "Kismet/GameplayStatics.h"
#include "AngryGameMode.h"

void ASpecialTarget::IncrementScore()
{
	float TimeAlive = GetWorld()->GetTimeSeconds() - GetGameTimeSinceCreation();

	const int32 MaxScore = 10;
	const int32 MinScore = 1;

	int32 FinalScore = FMath::Clamp(MaxScore - FMath::FloorToInt(TimeAlive), MinScore, MaxScore);

	AAngryGameMode* GameMode = Cast<AAngryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->AddScore(FinalScore);
	}
}
