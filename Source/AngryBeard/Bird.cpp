#include "Bird.h"

ABird::ABird()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    RootComponent = StaticMesh;

    StaticMesh->SetSimulatePhysics(true);
    StaticMesh->SetNotifyRigidBodyCollision(true);

    StaticMesh->OnComponentHit.AddDynamic(this, &ABird::OnHit);

    FieldSystem = CreateDefaultSubobject<UFieldSystemComponent>(TEXT("FieldSystem"));
    FieldSystem->SetupAttachment(RootComponent);
}

void ABird::BeginPlay()
{
    Super::BeginPlay();
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
    if (!FieldSystem) return;

    URadialVector* RadialVector = NewObject<URadialVector>(this);
    RadialVector->Magnitude = 1500.0f;
    RadialVector->Position = Hit.ImpactPoint;

    FieldSystem->ApplyPhysicsField(
        true,
        EFieldPhysicsType::Field_LinearImpulse,
        nullptr,
        RadialVector
    );

	Destroy();
}
