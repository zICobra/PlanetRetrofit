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
        if(UGameplayStatics::LoadGameFromSlot(GameInstance->SaveGame->SaveSlotName, 0))
        {
            BP_LoadGameButton->SetVisibility(ESlateVisibility::Visible);
        }
    }

    BP_NewGameButton->SetFocus();
    AddDelegates();
}

void UMainMenuUI::AddDelegates()
{
    BP_NewGameButton->OnClicked.BindUObject(this, &UMainMenuUI::OnNewGameButtonClicked);
    BP_LoadGameButton->OnClicked.BindUObject(this, &UMainMenuUI::OnLoadGameButtonClicked);
    BP_SettingsButton->OnClicked.BindUObject(this, &UMainMenuUI::OnSettingsButtonClicked);
    BP_ExitButton->OnClicked.BindUObject(this, &UMainMenuUI::OnExitButtonClicked);

    BP_NewGameButton->OnHovered.BindUObject(this, &UMainMenuUI::OnNewGameButtonHovered);
}

void UMainMenuUI::RemoveDelegates()
{
    BP_NewGameButton->OnClicked.Unbind();
    BP_LoadGameButton->OnClicked.Unbind();
    BP_SettingsButton->OnClicked.Unbind();
    BP_ExitButton->OnClicked.Unbind();

    BP_NewGameButton->OnHovered.Unbind();
}


#pragma region StartRegion
void UMainMenuUI::OnNewGameButtonClicked()
{
    RemoveDelegates();
    GameInstance->LoadGame = false;
    LoadMainLevel();
}

void UMainMenuUI::OnLoadGameButtonClicked()
{
    RemoveDelegates();
    GameInstance->LoadGame = true;
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

void UMainMenuUI::OnNewGameButtonHovered()
{
    if(UGameplayStatics::LoadGameFromSlot(GameInstance->SaveGame->SaveSlotName, 0))
    {
        NewGameWarning->SetVisibility(ESlateVisibility::Visible);
    }
}

void UMainMenuUI::OnNewGameButtonUnHovered()
{
    if(UGameplayStatics::LoadGameFromSlot(GameInstance->SaveGame->SaveSlotName, 0))
    {
        NewGameWarning->SetVisibility(ESlateVisibility::Collapsed);
    }
}
#pragma endregion StartRegion
