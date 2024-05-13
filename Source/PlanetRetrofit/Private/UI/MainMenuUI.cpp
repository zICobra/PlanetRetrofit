// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuUI.h"

#include "UI/ButtonBase.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "DefaultGameInstance.h"
#include "SaveGame/DefaultSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "CommonTextBlock.h"




void UMainMenuUI::NativeConstruct()
{
    Super::NativeConstruct();

    GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());
    if(GameInstance)
    {
        GameInstance->LoadSettingsInMenu();
    }

    BP_PlayButton->SetFocus();
    AddDelegates();
}

void UMainMenuUI::AddDelegates()
{
    BP_PlayButton->OnClicked.BindUObject(this, &UMainMenuUI::OnPlayButtonClicked);
    BP_SettingsButton->OnClicked.BindUObject(this, &UMainMenuUI::OnSettingsButtonClicked);
    BP_ExitButton->OnClicked.BindUObject(this, &UMainMenuUI::OnExitButtonClicked);
}

void UMainMenuUI::RemoveDelegates()
{
    BP_PlayButton->OnClicked.Unbind();
    BP_SettingsButton->OnClicked.Unbind();
    BP_ExitButton->OnClicked.Unbind();
}


#pragma region StartRegion
void UMainMenuUI::OnPlayButtonClicked()
{
    LoadMainLevel();
}


void UMainMenuUI::OnSettingsButtonClicked()
{
	SettingsButtonPressedDelegate.Broadcast();
}


void UMainMenuUI::OnExitButtonClicked()
{
    RemoveDelegates();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ConsoleCommand("quit");
}
#pragma endregion StartRegion
