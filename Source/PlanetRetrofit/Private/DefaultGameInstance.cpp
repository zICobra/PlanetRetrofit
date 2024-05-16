// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameInstance.h"

#include "SaveGame/DefaultSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"

#include "DataAssets/BuildingsConfig.h"



void UDefaultGameInstance::LoadSettingsInMenu()
{
    SaveGame = Cast<UDefaultSaveGame>(UGameplayStatics::CreateSaveGameObject(UDefaultSaveGame::StaticClass()));

    if (UDefaultSaveGame* LoadedGame = Cast<UDefaultSaveGame>(UGameplayStatics::LoadGameFromSlot(SettingsSaveSlotName, 0)))
    {
        SaveGame->MasterSliderVolume = LoadedGame->MasterSliderVolume;
        SaveGame->MusicSliderVolume = LoadedGame->MusicSliderVolume;
        SaveGame->SFXSliderVolume = LoadedGame->SFXSliderVolume;
        SetSettings();
    }
    else
    {
        SaveGame->MasterSliderVolume = 0.5f;
        SaveGame->MusicSliderVolume = 0.5f;
        SaveGame->SFXSliderVolume = 0.5f;
        SetSettings();
    }

}



void UDefaultGameInstance::LoadSettingsInMainLevel()
{
    SaveGame = Cast<UDefaultSaveGame>(UGameplayStatics::CreateSaveGameObject(UDefaultSaveGame::StaticClass()));
    
    if(UDefaultSaveGame* LoadedGame = Cast<UDefaultSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGame->SaveSlotName, 0)))
    {
        if(LoadGame)
        {
            SaveGame->StoneAmount = LoadedGame->StoneAmount;
            SaveGame->IronAmount = LoadedGame->IronAmount;
            SaveGame->CopperAmount = LoadedGame->CopperAmount;
            SaveGame->AmethystAmount = LoadedGame->AmethystAmount;
            SaveGame->PlatinAmount = LoadedGame->PlatinAmount;

            SaveGame->OxygenDepletionMultiplier = LoadedGame->OxygenDepletionMultiplier;

            SaveGame->TerminalSaveDataArray = LoadedGame->TerminalSaveDataArray;
            SaveGame->OreSaveDataArray = LoadedGame->OreSaveDataArray;
        }
        else
        {
            SaveGame->StoneAmount = 0;
            SaveGame->IronAmount = 0;
            SaveGame->CopperAmount = 0;
            SaveGame->AmethystAmount = 0;
            SaveGame->PlatinAmount = 0;

            SaveGame->OxygenDepletionMultiplier = 8.0f;

            SaveGame->TerminalSaveDataArray.Empty();
            SaveGame->OreSaveDataArray.Empty();
        }
    }
    else
    {
        SaveGame->StoneAmount = 0;
        SaveGame->IronAmount = 0;
        SaveGame->CopperAmount = 0;
        SaveGame->AmethystAmount = 0;
        SaveGame->PlatinAmount = 0;

        SaveGame->OxygenDepletionMultiplier = 8.0f;

        SaveGame->TerminalSaveDataArray.Empty();
        SaveGame->OreSaveDataArray.Empty();
    }

    if(UDefaultSaveGame* LoadedGame = Cast<UDefaultSaveGame>(UGameplayStatics::LoadGameFromSlot(SettingsSaveSlotName, 0)))
    {
        SaveGame->MasterSliderVolume = LoadedGame->MasterSliderVolume;
        SaveGame->MusicSliderVolume = LoadedGame->MusicSliderVolume;
        SaveGame->SFXSliderVolume = LoadedGame->SFXSliderVolume;

        SaveGame->MouseSensitivity = LoadedGame->MouseSensitivity;
        SaveGame->ControllerSensitivity = LoadedGame->ControllerSensitivity;
        SetSettings();
    }
    else
    {
        SaveGame->MasterSliderVolume = 0.5f;
        SaveGame->MusicSliderVolume = 0.5f;
        SaveGame->SFXSliderVolume = 0.5f;

        SaveGame->MouseSensitivity = 0.75f;
        SaveGame->ControllerSensitivity = 0.75f;
        SetSettings();
    }
}


void UDefaultGameInstance::SaveGameState()
{
    if(!SaveGame)
    {
        return;
    }
    if(UGameplayStatics::SaveGameToSlot(SaveGame, SaveGame->SaveSlotName, 0))
    {
        UE_LOG(LogTemp, Warning, TEXT("Saved"));
    }
}

void UDefaultGameInstance::SaveSettings()
{
    if(!SaveGame)
    {
        return;
    }
    if(UGameplayStatics::SaveGameToSlot(SaveGame, SettingsSaveSlotName, 0))
    {
        SetSettings();
    }
    
}

void UDefaultGameInstance::SetSettings()
{
    if(MasterSoundClass && MusicSoundClass && SFXSoundClass)
    {
        MasterSoundClass->Properties.Volume = SaveGame->MasterSliderVolume;
        MusicSoundClass->Properties.Volume = SaveGame->MusicSliderVolume;
        SFXSoundClass->Properties.Volume = SaveGame->SFXSliderVolume;
    }
}







