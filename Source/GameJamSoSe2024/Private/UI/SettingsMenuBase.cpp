// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SettingsMenuBase.h"

#include "UI/SliderBase.h"
#include "UI/ButtonBase.h"
#include "DefaultGameInstance.h"
#include "SaveGame/DefaultSaveGame.h"

void USettingsMenuBase::NativeConstruct()
{
    MasterSlider->OnSliderValueChanged.BindUObject(this, &USettingsMenuBase::MasterSliderValueChanged);
    MusicSlider->OnSliderValueChanged.BindUObject(this, &USettingsMenuBase::MusicSliderValueChanged);
    SFXSlider->OnSliderValueChanged.BindUObject(this, &USettingsMenuBase::SFXSliderValueChanged);
    MouseSensSlider->OnSliderValueChanged.BindUObject(this, &USettingsMenuBase::MouseSensSliderValueChanged);
    ControllerSensSlider->OnSliderValueChanged.BindUObject(this,&USettingsMenuBase::ControllerSensSliderValueChanged);
    BackButton->OnClicked.BindUObject(this, &USettingsMenuBase::BackButtonCalled); 

    MasterSlider->SetFocus();

    GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());
    if(GameInstance)
    {
        SetUpSliderValue();
    }
}

void USettingsMenuBase::SetUpSliderValue()
{
    MasterSlider->SetValue(GameInstance->SaveGame->MasterSliderVolume);
    MusicSlider->SetValue(GameInstance->SaveGame->MusicSliderVolume);
    SFXSlider->SetValue(GameInstance->SaveGame->SFXSliderVolume);
    MouseSensSlider->SetValue(GameInstance->SaveGame->MouseSensitivity);
    ControllerSensSlider->SetValue(GameInstance->SaveGame->ControllerSensitivity);
}

void USettingsMenuBase::RemoveDelegates()
{
    MasterSlider->OnSliderValueChanged.Unbind();
    MusicSlider->OnSliderValueChanged.Unbind();
    SFXSlider->OnSliderValueChanged.Unbind();
    MouseSensSlider->OnSliderValueChanged.Unbind();
    ControllerSensSlider->OnSliderValueChanged.Unbind();
    BackButton->OnClicked.Unbind(); 
}

void USettingsMenuBase::MasterSliderValueChanged(float NewValue)
{
    MasterSlider->SetValue(NewValue);
    GameInstance->SaveGame->MasterSliderVolume = NewValue;
    GameInstance->SaveSettings();
}

void USettingsMenuBase::MusicSliderValueChanged(float NewValue)
{
    MusicSlider->SetValue(NewValue);
    GameInstance->SaveGame->MusicSliderVolume = NewValue;
    GameInstance->SaveSettings();
}

void USettingsMenuBase::SFXSliderValueChanged(float NewValue)
{
    SFXSlider->SetValue(NewValue);
    GameInstance->SaveGame->SFXSliderVolume = NewValue;
    GameInstance->SaveSettings();
}

void USettingsMenuBase::MouseSensSliderValueChanged(float NewValue)
{
    MouseSensSlider->SetValue(NewValue);
    GameInstance->SaveGame->MouseSensitivity = NewValue;
    GameInstance->SaveSettings();
}

void USettingsMenuBase::ControllerSensSliderValueChanged(float NewValue)
{
    ControllerSensSlider->SetValue(NewValue);
    GameInstance->SaveGame->ControllerSensitivity = NewValue;
    GameInstance->SaveSettings();
}

void USettingsMenuBase::BackButtonCalled()
{
    RemoveDelegates();
    DeactivateWidget();
}

