// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh Component"));
	WeaponMesh->SetupAttachment(Root);
}

void ABaseWeapon::PullTrigger()
{
	const FTransform SpawnTransform = WeaponMesh->GetSocketTransform("WeaponSocket");
	UGameplayStatics::SpawnEmitterAtLocation(this, MuzzleFlash, WeaponMesh->GetSocketLocation("WeaponSocket"), WeaponMesh->GetSocketRotation("WeaponSocket"));
	UGameplayStatics::SpawnSoundAtLocation(this, MuzzleSound, WeaponMesh->GetSocketLocation("WeaponSocket"), WeaponMesh->GetSocketRotation("WeaponSocket"));
	// UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, WeaponMesh, TEXT("MuzzleSocket"));
	// UGameplayStatics::SpawnSoundAttached(MuzzleSound, WeaponMesh, TEXT("MuzzleSocket"));

	APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

	const FVector SpawnLocation = WeaponMesh->GetSocketLocation("WeaponSocket");
	// const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

	GetWorld()->SpawnActor<AActor>(BulletToSpawn, SpawnLocation, SpawnRotation);
}

float ABaseWeapon::GetFireRate()
{
	return FireRate;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
