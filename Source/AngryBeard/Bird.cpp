#include "Bird.h"

#include "Components/StaticMeshComponent.h"

#include "Field/FieldSystemComponent.h"
#include "Field/FieldSystemObjects.h"

#include "PhysicsEngine/RadialForceComponent.h"

#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"


ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
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

void ABird::ShootWithVelocity(const FVector& velocity)
{
	if (!StaticMesh) return;

	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetAngularDamping(20.0F);
	StaticMesh->SetPhysicsLinearVelocity(velocity);
}

void ABird::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}
