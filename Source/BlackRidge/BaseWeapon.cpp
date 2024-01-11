// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"

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

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	MaxBullets -= MagazineSize - CurrentBullets;
	CurrentBullets = MagazineSize;
	// CurrentReloadTimer = ReloadTime;
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::StartReloading()
{
	if (MaxBullets > 0)
	{
		Cast<ABaseCharacter>(GetOwner())->bIsReloading = true;
		bIsReloading = true;
		UE_LOG(LogTemp, Warning, TEXT("Reloading..."));
		GetWorldTimerManager()
			.SetTimer(ReloadTimerHandle, this, &ABaseWeapon::Reload, ReloadTime, false);
	}
}

void ABaseWeapon::Reload()
{
	if (MaxBullets >= MagazineSize - CurrentBullets)
	{
		MaxBullets -= MagazineSize - CurrentBullets;
		CurrentBullets = MagazineSize;
	}
	else if (MaxBullets + CurrentBullets <= MagazineSize)
	{
		CurrentBullets += MaxBullets;
		MaxBullets = 0;
	}

	UE_LOG(LogTemp, Warning, TEXT("Reloaded!"));

	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);

	Cast<ABaseCharacter>(GetOwner())->bIsReloading = false;
	bIsReloading = false;
}

void ABaseWeapon::PullTrigger()
{
	if (CurrentBullets > 0)
	{
		CurrentBullets--;
		UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentBullets);

		const FTransform SpawnTransform = WeaponMesh->GetSocketTransform("WeaponSocket");
		UGameplayStatics::SpawnEmitterAtLocation(this, MuzzleFlash, WeaponMesh->GetSocketLocation("WeaponSocket"), WeaponMesh->GetSocketRotation("WeaponSocket"));
		UGameplayStatics::SpawnSoundAtLocation(this, MuzzleSound, WeaponMesh->GetSocketLocation("WeaponSocket"), WeaponMesh->GetSocketRotation("WeaponSocket"));

		APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

		const FVector SpawnLocation = WeaponMesh->GetSocketLocation("WeaponSocket");

		GetWorld()->SpawnActor<AActor>(BulletToSpawn, SpawnLocation, SpawnRotation);
	}
	else
	{
		Cast<ABaseCharacter>(GetOwner())->bIsFiring = false;
	}
}

float ABaseWeapon::GetFireRate()
{
	return FireRate;
}

bool ABaseWeapon::GetIsReloading()
{
	return bIsReloading;
}

int ABaseWeapon::GetCurrentBullets()
{
	return CurrentBullets;
}

int ABaseWeapon::GetMaxBullets()
{
	return MaxBullets;
}
