// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DefaultSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAMSOSE2024_API UDefaultSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	int32 StoneAmount = 0;
	UPROPERTY()
	int32 IronAmount = 0;
	UPROPERTY()
	int32 CopperAmount = 0;
	UPROPERTY()
	int32 AmethystAmount = 0;
	UPROPERTY()
	int32 PlatinAmount = 0;
	
	UPROPERTY()
	FString SaveSlotName = "SavedGameState";

	UPROPERTY()
	float MasterSliderVolume = 0.5f;
	UPROPERTY()
	float MusicSliderVolume = 0.5f;
	UPROPERTY()
	float SFXSliderVolume = 0.5f;
	UPROPERTY()
	float MouseSensitivity = 0.75f;
	UPROPERTY()
	float ControllerSensitivity = 0.75f;
	UPROPERTY()
	bool IsInverted = false;




};
