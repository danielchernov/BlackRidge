// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "BaseWeapon.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetRelativeLocation(FVector(6, 0, 64));
	CameraComponent->bUsePawnControlRotation = true;
	BaseMesh->AttachToComponent(CameraComponent, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
	Weapon->AttachToComponent(BaseMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("GripPoint"));
	Weapon->SetOwner(this);
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
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &ABaseCharacter::DetectReload);
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

void ABaseCharacter::DetectReload()
{
	if (!bIsReloading)
	{
		ABaseWeapon *WeaponInHand = Cast<ABaseWeapon>(Weapon);
		WeaponInHand->StartReloading();
	}
}

void ABaseCharacter::StartFire()
{
	bIsFiring = true;

	GetWorldTimerManager()
		.SetTimer(TimerHandle_ReFire, this, &ABaseCharacter::FireShot, Weapon->GetFireRate(), true, 0);
}

void ABaseCharacter::StopFire()
{
	bIsFiring = false;

	GetWorldTimerManager().ClearTimer(TimerHandle_ReFire);
}

void ABaseCharacter::FireShot()
{
	if (!bIsReloading)
	{
		Weapon->PullTrigger();
	}
}

float ABaseCharacter::GetCurrentBullets() const
{
	return Weapon->GetCurrentBullets();
}

float ABaseCharacter::GetMaxBullets() const
{
	return Weapon->GetMaxBullets();
}
