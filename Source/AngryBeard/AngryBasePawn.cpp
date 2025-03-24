// Fill out your copyright notice in the Description page of Project Settings.

#include "AngryBasePawn.h"

#include "Components/ArrowComponent.h"
#include "EnhancedInputSubsystems.h"


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

	Mesh->SetupAttachment(RootComponent);
	BirdSpawnPoint->SetupAttachment(RootComponent);
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
	enhancedInput->BindAction(AimAction, ETriggerEvent::Completed, this, &AAngryBasePawn::Shoot);
}


void AAngryBasePawn::StartAim(const FInputActionInstance& Instance)
{
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector()*100, FColor::Green, false, 5.0F);
}

void AAngryBasePawn::Shoot(const FInputActionInstance& Instance)
{
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100, FColor::Red, false, 5.0F);
	if (Bird) {
		Bird->SetFree();
	}
}
