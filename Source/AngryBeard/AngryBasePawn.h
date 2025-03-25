// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"

#include "AngryBeard/Bird.h"

#include "AngryBasePawn.generated.h"

class UArrowComponent;


UCLASS()
class ANGRYBEARD_API AAngryBasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAngryBasePawn();

	UFUNCTION(BlueprintCallable)
	ABird* SpawnBird(const TSubclassOf<ABird>& birdClass);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Input functions.
private:

	UFUNCTION()
	void StartAim(const FInputActionInstance& Instance);

	UFUNCTION()
	void Aim(const FInputActionInstance& Instance);

	UFUNCTION()
	void Shoot(const FInputActionInstance& Instance);


public:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UArrowComponent* BirdSpawnPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* SlingSocket;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* AimAction;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABird> Bird;

private:

	// Cached position of the sling's "center" (bird's position at rest).
	FVector slingCenter;

	// Yaw-pitch of where we're aiming.
	FRotator aimRotation;
};
