// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

UCLASS()
class BLACKRIDGE_API ABaseBullet : public AActor
{
	GENERATED_BODY()

public:
	ABaseBullet();

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	FVector Speed;
	UPROPERTY(EditAnywhere)
	float Duration;
	UPROPERTY(EditAnywhere)
	float Damage;

	FTimerHandle Timer;
	void DestroyTimer();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *BulletMesh;

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent *CapsuleComponent;

	UPROPERTY(EditAnywhere)
	UParticleSystem *HitEffect;
	UPROPERTY(EditAnywhere)
	USoundBase *HitSound;
};
