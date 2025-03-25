#pragma once

#include "CoreMinimal.h"
#include "TargetActor.h"
#include "SpecialTarget.generated.h"

UCLASS()
class ANGRYBEARD_API ASpecialTarget : public ATargetActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void IncrementScore() override;

	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

    virtual void SpawnFieldSystem() override;

    virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Target|Visual")
	UMaterialInterface* DamagedMaterial;
	int32 FinalScore = 100;

};
