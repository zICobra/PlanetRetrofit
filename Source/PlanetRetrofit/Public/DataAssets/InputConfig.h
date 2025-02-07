// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputConfig.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()

public: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputControllerLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputSprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputControllerSprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputJump;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputInteract;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputPauseMenu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputPullUpMaterialUI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMine;

};
