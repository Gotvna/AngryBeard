#pragma once

#include "CoreMinimal.h"
#include "TargetActor.h"
#include "SpecialTarget.generated.h"

UCLASS()
class ANGRYBEARD_API ASpecialTarget : public ATargetActor
{
	GENERATED_BODY()

protected:
	virtual void IncrementScore() override;
};
