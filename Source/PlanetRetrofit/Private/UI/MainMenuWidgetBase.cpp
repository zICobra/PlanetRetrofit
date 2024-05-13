// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidgetBase.h"

#include "UI/MainMenuUI.h"
#include "UI/SettingsMenuBase.h"


void UMainMenuWidgetBase::PushMainMenuUI(UMainMenuUI* MainMenuUI)
{
    if(MainMenuUI)
    {
        ContentStack->AddWidgetInstance(*MainMenuUI);
    }
}


void UMainMenuWidgetBase::PushSettingsMenu(USettingsMenuBase* SettingsMenu)
{
    if(SettingsMenu)
    {
        ContentStack->AddWidgetInstance(*SettingsMenu);
    }
}

