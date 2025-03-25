// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AngryGameMode.generated.h"

class ABird;
class AAngryBasePawn;

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32, NewScore);

UCLASS()
class ANGRYBEARD_API AAngryGameMode : public AGameMode
{
	GENERATED_BODY()
	
	AAngryGameMode();

	virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Score")
    int32 GetScore() const;

	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnScoreChanged OnScoreChanged;


public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray< TSubclassOf<ABird> > BirdsToSpawn;

private:

    int32 Score;

	AAngryBasePawn* Slingshot;
};
