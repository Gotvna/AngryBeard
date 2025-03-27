#include "Bird.h"

ABird::ABird()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ABird::BeginPlay()
{
    Super::BeginPlay();
    StaticMesh->OnComponentHit.AddDynamic(this, &ABird::OnHit);
}

void ABird::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABird::ShootWithVelocity(const FVector& velocity)
{
    StaticMesh->SetPhysicsLinearVelocity(velocity);
}

void ABird::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}
