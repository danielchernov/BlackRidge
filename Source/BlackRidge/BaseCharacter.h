// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class BLACKRIDGE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void StartFire();
	void StopFire();
	void FireShot();

	FTimerHandle TimerHandle_ReFire;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsFiring = false;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BulletToSpawn;
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<USceneComponent> GunComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MuzzleOffset;

	// UPROPERTY(EditAnywhere)
	// TSubclassOf<USceneComponent> GunMesh;

private:
	void MoveForward(float AxisValue);
	void LookUp(float AxisValue);
	void LookUpRate(float AxisValue);
	void MoveRight(float AxisValue);
	void LookRight(float AxisValue);
	void LookRightRate(float AxisValue);

	UPROPERTY(EditAnywhere)
	float RotationRate = 70;

	UPROPERTY(EditAnywhere)
	float FireRate = 0.5f;

	UPROPERTY(EditAnywhere)
	UParticleSystem *MuzzleFlash;
	UPROPERTY(EditAnywhere)
	USoundBase *MuzzleSound;
};
