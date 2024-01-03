// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBullet.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseBullet::ABaseBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh->SetupAttachment(CapsuleComponent);

	CapsuleComponent->OnComponentHit.AddDynamic(this, &ABaseBullet::OnHit);
}

void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(Timer, this, &ABaseBullet::DestroyTimer, Duration);
}

void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(Speed, true);
}

void ABaseBullet::DestroyTimer()
{
	Destroy();
}

void ABaseBullet::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit!!!"));

	FVector ShotDirection = -AActor::GetActorRotation().Vector();

	UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, Hit.ImpactPoint, ShotDirection.Rotation());
	UGameplayStatics::SpawnSoundAtLocation(this, HitSound, Hit.ImpactPoint, ShotDirection.Rotation());

	Destroy();
}
