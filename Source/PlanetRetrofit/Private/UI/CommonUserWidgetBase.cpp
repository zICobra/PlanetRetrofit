// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CommonUserWidgetBase.h"

#include "UI/CommonActivatableWidgetBase.h"




void UCommonUserWidgetBase::PushGamePlayMenu(UCommonActivatableWidgetBase* GamePlayMenu)
{
    if(GameplayStack->GetWidgetList().IsEmpty())
    {
        GameplayStack->AddWidgetInstance(*GamePlayMenu);
    }
}


void UCommonUserWidgetBase::PushPauseMenu(UCommonActivatableWidgetBase* PauseMenu)
{
    if(PauseMenu && PauseMenuStack->GetWidgetList().IsEmpty())
    {
        PauseMenuActive = true;
        PauseMenuStack->AddWidgetInstance(*PauseMenu);
    }
}


void UCommonUserWidgetBase::ClearPauseMenu()
{
    PauseMenuActive = false;
    PauseMenuStack->ClearWidgets();
}

void UCommonUserWidgetBase::PushSettingsMenu(UCommonActivatableWidgetBase* SettingsMenu)
{
    if(SettingsMenu)
    {
        PauseMenuActive = true;
        PauseMenuStack->AddWidgetInstance(*SettingsMenu);
    }
}

void UCommonUserWidgetBase::ClearSettingsMenu()
{
    PauseMenuStack->ClearWidgets();
}

void UCommonUserWidgetBase::PushBuildingMenu(class UCommonActivatableWidgetBase* BuildingMenu)
{
    if(BuildingMenu)
    {
        BuildingMenuActive = true;
        PauseMenuStack->AddWidgetInstance(*BuildingMenu);
    }
}

void UCommonUserWidgetBase::ClearBuildingMenu()
{
    BuildingMenuActive = true;
    PauseMenuStack->ClearWidgets();    
}

void UCommonUserWidgetBase::PushDeathScreen(class UCommonActivatableWidgetBase* DeathScreen)
{
    if(DeathScreen)
    {
        DeathScreenActive = true;
        PauseMenuStack->AddWidgetInstance(*DeathScreen);
    }
}




