#include "SpecialTarget.h"
#include "Kismet/GameplayStatics.h"
#include "AngryGameMode.h"

void ASpecialTarget::BeginPlay()
{
	Super::BeginPlay();
	bMaterialSwapped = false;
}

void ASpecialTarget::IncrementScore()
{
	float TimeAlive = GetGameTimeSinceCreation();

	const int32 MaxScore = 100;
	const int32 MinScore = 10;

	int32 FinalScore = FMath::Clamp(MaxScore - FMath::FloorToInt(TimeAlive), MinScore, MaxScore);

	if (FinalScore < MaxScore && !bMaterialSwapped && DamagedMaterial)
	{
		MeshComponent->SetMaterial(0, DamagedMaterial);
		bMaterialSwapped = true;
	}

	AAngryGameMode* GameMode = Cast<AAngryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->AddScore(FinalScore);
	}
}

void ASpecialTarget::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->ActorHasTag("Bullet"))
	{
		IncrementScore();
		Destroy();
	}
}
