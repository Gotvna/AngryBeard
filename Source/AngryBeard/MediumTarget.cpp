#include "MediumTarget.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AngryGameMode.h"


AMediumTarget::AMediumTarget()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AMediumTarget::OnHit);
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

	UE_LOG(LogTemp, Warning, TEXT("Hit"));
	if (OtherActor && OtherActor->ActorHasTag("Bullet"))
	{
		IncrementScore();
		Destroy();
	}
}