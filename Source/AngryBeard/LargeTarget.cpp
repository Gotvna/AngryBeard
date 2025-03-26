#include "LargeTarget.h"
#include "Kismet/GameplayStatics.h"
#include "AngryGameMode.h"

int32 ALargeTarget::GetBaseScore() const
{
	return 50;
}

void ALargeTarget::IncrementScore()
{
	AAngryGameMode* GameMode = Cast<AAngryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->AddScore(GetBaseScore());
	}
}

void ALargeTarget::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->ActorHasTag("Bullet"))
	{
		IncrementScore();
		SpawnFieldSystem();
		Destroy();
	}
}

void ALargeTarget::SpawnFieldSystem()
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