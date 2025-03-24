#include "AngryGameMode.h"

AAngryGameMode::AAngryGameMode()
{
	Score = 0;
}

void AAngryGameMode::AddScore(int32 Amount)
{
    Score += Amount;
	OnScoreChanged.Broadcast(Score);
}

int32 AAngryGameMode::GetScore() const
{
    return Score;
}