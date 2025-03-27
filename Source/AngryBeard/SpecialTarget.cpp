#include "SpecialTarget.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AngryGameMode.h"
#include "Field/FieldSystemActor.h"

void ASpecialTarget::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASpecialTarget::OnHit);

}

void ASpecialTarget::IncrementScore()
{
	AAngryGameMode* GameMode = Cast<AAngryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->AddScore(FinalScore);
	}
}

void ASpecialTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TimeAlive = GetGameTimeSinceCreation();

	const int32 MaxScore = 100;
	const int32 MinScore = 10;

	int32 NewScore = FMath::Clamp(MaxScore - (FMath::FloorToInt(TimeAlive / 1.f) * 10), MinScore, MaxScore);

	if (NewScore != FinalScore)
	{
		FinalScore = NewScore;
	}
}

