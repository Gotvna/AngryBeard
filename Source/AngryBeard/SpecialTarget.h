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

    virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Target|Visual")
	UMaterialInterface* DamagedMaterial;

	int32 FinalScore = 100;

	bool bMaterialSwapped = false;

public:
	class UBoxComponent* CollisionComponent;

};
