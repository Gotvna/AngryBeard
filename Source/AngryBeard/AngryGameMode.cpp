#include "AngryGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "AngryBeard/AngryBasePawn.h"


AAngryGameMode::AAngryGameMode()
{
	Score = 0;
}

void AAngryGameMode::BeginPlay()
{
	Super::BeginPlay();

	Slingshot = Cast<AAngryBasePawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	SpawnNextBird();
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


void AAngryGameMode::SpawnNextBird()
{
	if (Slingshot && !BirdsToSpawn.IsEmpty()) {
		TSubclassOf<ABird> birdType = BirdsToSpawn.Pop();
		Slingshot->SpawnBird(birdType);
	}
}

int32 AAngryGameMode::GetRemainingBirds() const
{
	return BirdsToSpawn.Num();
}
