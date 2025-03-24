// Fill out your copyright notice in the Description page of Project Settings.


#include "AngryGameMode.h"

AAngryGameMode::AAngryGameMode()
{
	Score = 0;
}

void AAngryGameMode::AddScore(int32 Amount)
{
    Score += Amount;
    UE_LOG(LogTemp, Log, TEXT("Score increased: %d"), Score);
}

int32 AAngryGameMode::GetScore() const
{
    return Score;
}