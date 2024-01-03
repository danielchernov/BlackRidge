// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBullet.h"
#include "TimerManager.h"

ABaseBullet::ABaseBullet()
{
	PrimaryActorTick.bCanEverTick = true;
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
