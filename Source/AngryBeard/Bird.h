// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bird.generated.h"

class UStaticMeshComponent;
class UFieldSystemComponent;
class UParticleSystemComponent;


UCLASS()
class ANGRYBEARD_API ABird : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABird();

	void ShootWithVelocity(const FVector& velocity);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	UFieldSystemComponent* FieldSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
	UParticleSystemComponent* ImpactParticleComponent;

	UPROPERTY(EditAnywhere, Category = "Effects")
	float ImpactThreshold = 500.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
