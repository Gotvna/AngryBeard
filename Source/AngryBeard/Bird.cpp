// Bird.cpp

#include "Bird.h"
#include "Components/StaticMeshComponent.h"

ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetNotifyRigidBodyCollision(true);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionObjectType(ECC_PhysicsBody);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Block);
}

void ABird::BeginPlay()
{
	Super::BeginPlay();
	if (StaticMesh)
	{
		StaticMesh->OnComponentHit.AddDynamic(this, &ABird::OnHit);
	}
}

void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABird::ShootWithVelocity(const FVector& Velocity)
{
	if (StaticMesh)
	{
		StaticMesh->SetPhysicsLinearVelocity(Velocity);
	}
}

void ABird::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}
