#include "TargetActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AngryGameMode.h"

ATargetActor::ATargetActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->SetSimulatePhysics(true);
}

void ATargetActor::BeginPlay()
{
	Super::BeginPlay();

	SpawnTime = GetWorld()->GetTimeSeconds();
	CollisionComponent->OnComponentHit.AddDynamic(this, &ATargetActor::OnHit);
}

void ATargetActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATargetActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->ActorHasTag("Bullet"))
	{
		IncrementScore();
		SelfDestruct();
	}
}

void ATargetActor::IncrementScore()
{
	AAngryGameMode* GameMode = Cast<AAngryGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->AddScore(GetBaseScore());
	}
}

int32 ATargetActor::GetBaseScore() const
{
	return 1;
}

void ATargetActor::SelfDestruct()
{
	GetWorld()->GetTimerManager().SetTimer(SelfDestructTimerHandle, this, &ATargetActor::HandleSelfDestruct, 2.0f, false);
}

void ATargetActor::HandleSelfDestruct()
{
	Destroy();
}