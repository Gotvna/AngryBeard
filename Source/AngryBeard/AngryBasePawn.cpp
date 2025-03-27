// Fill out your copyright notice in the Description page of Project Settings.

#include "AngryBasePawn.h"

#include "Components/ArrowComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AAngryBasePawn::AAngryBasePawn()
	: AimAction(NULL)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	BirdSpawnPoint = CreateDefaultSubobject<UArrowComponent>("BirdSpawnPoint");
	SlingSocket = CreateDefaultSubobject<UStaticMeshComponent>("SlingSocket");

	Mesh->SetupAttachment(RootComponent);
	BirdSpawnPoint->SetupAttachment(RootComponent);
	SlingSocket->SetupAttachment(RootComponent);
}

ABird* AAngryBasePawn::SpawnBird(const TSubclassOf<ABird>& birdClass)
{
	Bird = GetWorld()->SpawnActor<ABird>(birdClass.Get(), slingCenter, FRotator());

	SlingSocket->SetSimulatePhysics(false);
	SlingSocket->SetWorldLocation(slingCenter);

	return Bird;
}

void AAngryBasePawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	slingCenter = BirdSpawnPoint->GetComponentLocation();
}

void AAngryBasePawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAngryBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAngryBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);


	UEnhancedInputComponent* enhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	enhancedInput->BindAction(AimAction, ETriggerEvent::Started, this, &AAngryBasePawn::StartAim);
	enhancedInput->BindAction(AimAction, ETriggerEvent::Ongoing, this, &AAngryBasePawn::Aim);
	enhancedInput->BindAction(AimAction, ETriggerEvent::Completed, this, &AAngryBasePawn::Shoot);
}


void AAngryBasePawn::StartAim(const FInputActionInstance& Instance)
{
	
}

void AAngryBasePawn::Aim(const FInputActionInstance& Instance)
{
	if (!Bird) return;

	double mouseX, mouseY;
	int viewportX, viewportY;

	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
	playerController->bShowMouseCursor = true;
	playerController->GetMousePosition(mouseX, mouseY);
	playerController->GetViewportSize(viewportX, viewportY);

	double mouseRelX = (mouseX / viewportX) - 0.5, mouseRelY = (mouseY / viewportY) - 0.5;
	aimRotation = FRotator(mouseRelY * 80.0, mouseRelX * -120.0, 0.0);

	FVector socketPos = slingCenter - UKismetMathLibrary::GetForwardVector(aimRotation) * 100.0;
	Bird->SetActorLocation(socketPos);
	SlingSocket->SetWorldLocation(socketPos);

	// Predict trajectory
	FVector launchVelocity = UKismetMathLibrary::GetForwardVector(aimRotation) * 1800.0;

	FPredictProjectilePathParams pathParams;
	pathParams.StartLocation = socketPos;
	pathParams.LaunchVelocity = launchVelocity;
	pathParams.bTraceWithCollision = true;
	pathParams.ProjectileRadius = 5.0f;
	pathParams.MaxSimTime = 2.0f;
	pathParams.SimFrequency = 15.0f;
	pathParams.TraceChannel = ECC_Visibility;
	pathParams.OverrideGravityZ = 0.0f;

	FPredictProjectilePathResult pathResult;

	bool hit = UGameplayStatics::PredictProjectilePath(this, pathParams, pathResult);

	for (const FPredictProjectilePathPointData& point : pathResult.PathData)
	{
		DrawDebugPoint(
			GetWorld(),
			point.Location,
			8.0f,
			FColor::Green,
			false
		);
	}
}

void AAngryBasePawn::Shoot(const FInputActionInstance& Instance)
{
	if (Bird) {
		FVector vel = UKismetMathLibrary::GetForwardVector(aimRotation) * 1800.0;
		Bird->ShootWithVelocity(vel);
		SlingSocket->SetSimulatePhysics(true);
		SlingSocket->SetPhysicsLinearVelocity(vel);
	}
}
