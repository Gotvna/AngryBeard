#include "SpecialTarget.h"
#include "Kismet/GameplayStatics.h"
#include "AngryGameMode.h"
#include "Field/FieldSystemActor.h"

void ASpecialTarget::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;

}

void ASpecialTarget::IncrementScore()
{
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
		SpawnFieldSystem();
		Destroy();
	}
}

void ASpecialTarget::SpawnFieldSystem()
{
	Super::SpawnFieldSystem();

}

void ASpecialTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TimeAlive = GetGameTimeSinceCreation();

	const int32 MaxScore = 100;
	const int32 MinScore = 10;

	int32 NewScore = FMath::Clamp(MaxScore - FMath::FloorToInt(TimeAlive), MinScore, MaxScore);

	if (NewScore != FinalScore)
	{
		FinalScore = NewScore;
		UE_LOG(LogTemp, Warning, TEXT("SpecialTarget Score: %d"), FinalScore);
	}

	if (FinalScore <= 90 && DamagedMaterial)
	{
		MeshComponent->SetMaterial(0, DamagedMaterial);
	}
}

