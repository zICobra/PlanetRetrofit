// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"


#include "UI/MainMenuWidgetBase.h"
#include "UI/MainMenuUI.h"
#include "UI/SettingsMenuBase.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGameMode::BeginPlay()
{
    if(MainMenuUIBase)
    {
        CreatedMainMenuBase = Cast<UMainMenuWidgetBase>(CreateWidget<UCommonUserWidget>(GetWorld(), MainMenuUIBase));
        CreatedMainMenuBase->AddToViewport(0);
    }
    if(MainMenuUI)
    {
        CreatedMainMenuUI = Cast<UMainMenuUI>(CreateWidget<UCommonActivatableWidgetBase>(GetWorld(), MainMenuUI));
        CreatedMainMenuUI->SettingsButtonPressedDelegate.AddUniqueDynamic(this, &AMainMenuGameMode::SettingsMenuCalled);
    }
    if(SettingsMenu)
    {
        CreatedSettingsMenu = Cast<USettingsMenuBase>(CreateWidget<UCommonActivatableWidgetBase>(GetWorld(), SettingsMenu));
    }
    
    CreatedMainMenuBase->PushMainMenuUI(CreatedMainMenuUI);


    UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
}

void AMainMenuGameMode::SettingsMenuCalled()
{
    CreatedMainMenuBase->PushSettingsMenu(CreatedSettingsMenu);
}

