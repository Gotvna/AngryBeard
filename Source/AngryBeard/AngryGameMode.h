// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AngryGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ANGRYBEARD_API AAngryGameMode : public AGameMode
{
	GENERATED_BODY()
	
	AAngryGameMode();

public:
    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Score")
    int32 GetScore() const;

private:
    int32 Score;
};
