// Fill out your copyright notice in the Description page of Project Settings.


#include "F1PlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AF1PlayerController::AF1PlayerController()
{
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AF1PlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);
}

void AF1PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("SetNewDestination", IE_Pressed, this, &AF1PlayerController::OnSetNewDestination_Pressed);
    InputComponent->BindAction("SetNewDestination", IE_Released, this, &AF1PlayerController::OnSetNewDestination_Released);
}

void AF1PlayerController::OnSetNewDestination_Pressed()
{
    MoveToMouseCursor();
}

void AF1PlayerController::OnSetNewDestination_Released()
{

}

void AF1PlayerController::MoveToMouseCursor()
{
    FHitResult hit;
    GetHitResultUnderCursor(ECC_Visibility, false, hit);
    if (hit.bBlockingHit)
    {
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, hit.ImpactPoint);
    }
}