#pragma once

#include "CoreMinimal.h"
#include "TargetActor.h"
#include "LargeTarget.generated.h"

UCLASS()
class ANGRYBEARD_API ALargeTarget : public ATargetActor
{
	GENERATED_BODY()

protected:
	virtual int32 GetBaseScore() const override;

	virtual void IncrementScore() override;

public:

};
