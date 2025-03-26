#include "MediumTarget.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AngryGameMode.h"


AMediumTarget::AMediumTarget()
{
	
}

void AMediumTarget::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
}

int32 AMediumTarget::GetBaseScore() const
{
	return 20;
}

void AMediumTarget::IncrementScore()
{
	AAngryGameMode* GameMode = Cast<AAngryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->AddScore(GetBaseScore());
	}
}

void AMediumTarget::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->ActorHasTag("Bullet"))
	{
		IncrementScore();
		SpawnFieldSystem();
		Destroy();
	}
}


void AMediumTarget::SpawnFieldSystem()
{
	if (ExplosionFieldClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AFieldSystemActor>(
			ExplosionFieldClass,
			GetActorLocation(),
			FRotator::ZeroRotator,
			SpawnParams
		);
	}
}