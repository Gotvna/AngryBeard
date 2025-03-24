#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetActor.generated.h"

UCLASS()
class ANGRYBEARD_API ATargetActor : public AActor
{
	GENERATED_BODY()

public:
	ATargetActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

	virtual void IncrementScore();

	virtual int32 GetBaseScore() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionComponent;

private:
	float SpawnTime;
};
