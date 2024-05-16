// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DefaultGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API UDefaultGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	class USoundClass* MasterSoundClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	class USoundClass* MusicSoundClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	class USoundClass* SFXSoundClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataAssets")
	class UBuildingsConfig* BuildingConfig = nullptr;

	bool LoadGame = false;
	FString SettingsSaveSlotName = "SavedSettings";
	
	void LoadSettingsInMenu();

	void LoadSettingsInMainLevel();

	void SaveGameState();

	void SaveSettings();
	void SetSettings();

	UPROPERTY()
	class UDefaultSaveGame* SaveGame;

	DECLARE_DELEGATE(FOnSettingsMainMenu);
	FOnSettingsMainMenu OreLoadedSettingsDelegate;
	FOnSettingsMainMenu TerminalLoadedSettingsDelegate;

};
