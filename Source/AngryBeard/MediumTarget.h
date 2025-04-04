#pragma once

#include "CoreMinimal.h"
#include "TargetActor.h"
#include "MediumTarget.generated.h"

UCLASS()
class ANGRYBEARD_API AMediumTarget : public ATargetActor
{
	GENERATED_BODY()

protected:
	AMediumTarget();

	virtual void BeginPlay() override;
	virtual int32 GetBaseScore() const override;

	virtual void IncrementScore() override;
};
