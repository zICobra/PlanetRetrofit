// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidgetBase.h"

#include "UI/MainMenuUI.h"
#include "UI/SettingsMenuBase.h"

#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidgetBase::PushMainMenuUI(UMainMenuUI* MainMenuUI)
{
    if(MainMenuUI)
    {
        ContentStack->AddWidgetInstance(*MainMenuUI);
    }
    UGameplayStatics::PlaySound2D(GetWorld(), BGMusic);
}


void UMainMenuWidgetBase::PushSettingsMenu(USettingsMenuBase* SettingsMenu)
{
    if(SettingsMenu)
    {
        ContentStack->AddWidgetInstance(*SettingsMenu);
    }
}

