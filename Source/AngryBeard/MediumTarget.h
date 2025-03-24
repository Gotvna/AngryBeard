#pragma once

#include "CoreMinimal.h"
#include "TargetActor.h"
#include "MediumTarget.generated.h"

UCLASS()
class ANGRYBEARD_API AMediumTarget : public ATargetActor
{
	GENERATED_BODY()

protected:
	virtual void IncrementScore() override;
};
