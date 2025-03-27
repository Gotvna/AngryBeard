#include "MediumTarget.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AngryGameMode.h"


AMediumTarget::AMediumTarget()
{

	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

void AMediumTarget::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentHit.AddDynamic(this, &AMediumTarget::OnHit);
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
		UE_LOG(LogTemp, Warning, TEXT("Bullet Hit '%s'"), *OtherActor->GetName());
		IncrementScore();
		Destroy();
	}
}

void AMediumTarget::SelfDestruct()
{
}
