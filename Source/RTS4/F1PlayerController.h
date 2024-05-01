// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "F1PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RTS4_API AF1PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AF1PlayerController();

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void OnSetNewDestination_Pressed();
	void OnSetNewDestination_Released();
	void MoveToMouseCursor();
};
