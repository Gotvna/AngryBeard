// Fill out your copyright notice in the Description page of Project Settings.

#include "AngryBasePawn.h"

#include "Components/ArrowComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


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
	Bird = GetWorld()->SpawnActor<ABird>(birdClass.Get(), BirdSpawnPoint->GetComponentLocation(), BirdSpawnPoint->GetComponentRotation());
	return Bird;
}

// Called when the game starts or when spawned
void AAngryBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
	slingCenter = BirdSpawnPoint->GetComponentLocation();
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
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector()*100, FColor::Green, false, 5.0F);
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

	FVector socketPos(slingCenter - UKismetMathLibrary::GetForwardVector(aimRotation) * 100.0);
	Bird->SetActorLocation(socketPos);
	SlingSocket->SetWorldLocation(socketPos);
}

void AAngryBasePawn::Shoot(const FInputActionInstance& Instance)
{
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100, FColor::Red, false, 5.0F);
	if (Bird) {
		FVector vel = UKismetMathLibrary::GetForwardVector(aimRotation) * 1800.0;
		Bird->ShootWithVelocity(vel);
		SlingSocket->SetSimulatePhysics(true);
		SlingSocket->SetPhysicsLinearVelocity(vel);
	}
}
