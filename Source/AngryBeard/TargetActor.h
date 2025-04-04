#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Field/FieldSystemActor.h"
#include "TargetActor.generated.h"

class AFieldSystemActor;

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
    virtual void Tick(float DeltaTime);
	void SelfDestruct();

	UFUNCTION()
	void HandleSelfDestruct();
protected:
	float SpawnTime;

	FTimerHandle SelfDestructTimerHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionComponent;

};
