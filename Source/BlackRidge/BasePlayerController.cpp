// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerController.h"
#include "Blueprint/UserWidget.h"

void ABasePlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUD = CreateWidget(this, HUDClass);
    if (HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}