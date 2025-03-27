// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h" // Add Niagara include
#include "NiagaraFunctionLibrary.h" // Add Niagara include
#include "Bird.generated.h"

class UStaticMeshComponent;
class UFieldSystemComponent;

UCLASS()
class ANGRYBEARD_API ABird : public AActor
{
    GENERATED_BODY()

public:
    ABird();

    void ShootWithVelocity(const FVector& velocity);

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* StaticMesh;

    UPROPERTY(EditAnywhere)
    UFieldSystemComponent* FieldSystem;

    UPROPERTY(EditAnywhere, Category = "Effects")
    class UNiagaraSystem* ImpactNiagaraSystem; // Changed to Niagara system

    UPROPERTY(EditAnywhere, Category = "Effects")
    float ImpactThreshold = 500.0f;

    UPROPERTY(EditAnywhere, Category = "Effects", meta = (ClampMin = "0.1", ClampMax = "10.0"))
    float ParticleScale = 0.5f;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};