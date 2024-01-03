// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// TArray<USceneComponent *> SkeletalMeshComponentArray2;

	// TArray<AActor *> AttachedActors;
	// GetAttachedActors(AttachedActors);
	// for (auto *Attached : AttachedActors)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("%s"), *Attached->GetName());

	// 	// USceneComponent *AttachedSceneComponent = Cast<USceneComponent>(Attached);
	// 	// FVector SocketLocation = AttachedSceneComponent->GetSocketLocation("MuzzleSocket");
	// 	// UE_LOG(LogTemp, Warning, TEXT("%f"), SocketLocation);
	// }
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABaseCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ABaseCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &ABaseCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ABaseCharacter::LookRightRate);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ABaseCharacter::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &ABaseCharacter::StopFire);
}

void ABaseCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ABaseCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ABaseCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ABaseCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ABaseCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::StartFire()
{
	bIsFiring = true;

	GetWorldTimerManager().SetTimer(TimerHandle_ReFire, this, &ABaseCharacter::FireShot, FireRate, true, 0);

	UE_LOG(LogTemp, Warning, TEXT("Firing"));
}

void ABaseCharacter::StopFire()
{
	bIsFiring = false;

	GetWorldTimerManager().ClearTimer(TimerHandle_ReFire);

	UE_LOG(LogTemp, Warning, TEXT("Stopped Firing"));
}

void ABaseCharacter::FireShot()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, this->GetMesh(), TEXT("MuzzleSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, this->GetMesh(), TEXT("MuzzleSocket"));

	APlayerController *PlayerController = Cast<APlayerController>(this->GetController());
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

	// Set Spawn Collision Handling Override
	// FActorSpawnParameters ActorSpawnParams;
	// ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	// Spawn the projectile at the muzzle
	GetWorld()->SpawnActor<AActor>(BulletToSpawn, SpawnLocation, SpawnRotation);
}
