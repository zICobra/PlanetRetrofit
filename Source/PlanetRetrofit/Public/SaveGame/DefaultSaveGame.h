// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DefaultSaveGame.generated.h"

/**
 * 
 */

USTRUCT()
struct FTerminalSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<class ABuildingInteractableBase> Terminal;
	UPROPERTY()
	bool HasSpawned = false;
	UPROPERTY()
	int32 BuildingIndex = 0;
	UPROPERTY()
	FVector Location = FVector(0, 0, 0);
};

USTRUCT()
struct FOreSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<class AOreBase> OreType;
	UPROPERTY()
	FVector Location;
	UPROPERTY()
	bool IsMined = false;
};

UCLASS()
class PLANETRETROFIT_API UDefaultSaveGame : public USaveGame
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
	float OxygenDepletionMultiplier = 4.0f;
	UPROPERTY()
	TArray<FTerminalSaveData> TerminalSaveDataArray;
	UPROPERTY()
	TArray<FOreSaveData> OreSaveDataArray;
	
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
