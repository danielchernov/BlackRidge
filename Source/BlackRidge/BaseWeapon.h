// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class BLACKRIDGE_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

	void PullTrigger();
	float GetFireRate();
	void StartReloading();
	void Reload();
	bool GetIsReloading();

	int GetCurrentBullets();
	int GetMaxBullets();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent *Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent *WeaponMesh;

	UPROPERTY(EditAnywhere)
	float FireRate = 0.5f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BulletToSpawn;

	UPROPERTY(EditAnywhere)
	UParticleSystem *MuzzleFlash;
	UPROPERTY(EditAnywhere)
	USoundBase *MuzzleSound;

	UPROPERTY(EditAnywhere)
	int MagazineSize = 10;
	UPROPERTY(EditAnywhere)
	int MaxBullets = 100;

	int CurrentBullets = 0;

	UPROPERTY(EditAnywhere)
	float ReloadTime = 2;
	FTimerHandle ReloadTimerHandle;

	bool bIsReloading = false;
};
