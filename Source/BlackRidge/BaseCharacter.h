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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsReloading = false;

	UFUNCTION(BlueprintPure)
	float GetCurrentBullets() const;
	UFUNCTION(BlueprintPure)
	float GetMaxBullets() const;

private:
	void MoveForward(float AxisValue);
	void LookUp(float AxisValue);
	void LookUpRate(float AxisValue);
	void MoveRight(float AxisValue);
	void LookRight(float AxisValue);
	void LookRightRate(float AxisValue);
	void DetectReload();

	UPROPERTY(EditAnywhere)
	float RotationRate = 70;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseWeapon> WeaponClass;

	UPROPERTY()
	class ABaseWeapon *Weapon;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent *CameraComponent;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent *BaseMesh;
};
