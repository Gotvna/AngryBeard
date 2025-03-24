#include "TargetActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AngryGameMode.h"

ATargetActor::ATargetActor()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName("BlockAll");
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ATargetActor::OnHit);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATargetActor::BeginPlay()
{
	Super::BeginPlay();
	SpawnTime = GetWorld()->GetTimeSeconds();
}

void ATargetActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (OtherActor && OtherActor->ActorHasTag("Bullet"))
	{
		IncrementScore();
		Destroy();
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
