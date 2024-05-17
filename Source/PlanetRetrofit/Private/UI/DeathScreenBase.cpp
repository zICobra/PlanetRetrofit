// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DeathScreenBase.h"

#include "UI/ButtonBase.h"
#include "Components/VerticalBox.h"

#include "DefaultGameInstance.h"
#include "SaveGame/DefaultSaveGame.h"
#include "Kismet/GameplayStatics.h"


void UDeathScreenBase::NativeConstruct()
{
    Super::NativeConstruct();

    GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());
    if(GameInstance)
    {
        if(UGameplayStatics::LoadGameFromSlot(GameInstance->SaveGame->SaveSlotName, 0))
        {
            LoadGameButton->SetVisibility(ESlateVisibility::Visible);
        }
    }
    AddDelegates();

    NewGameButton->SetFocus();
}

void UDeathScreenBase::AddDelegates()
{
    NewGameButton->OnClicked.BindUObject(this, &UDeathScreenBase::OnNewGameButtonClicked);
    LoadGameButton->OnClicked.BindUObject(this, &UDeathScreenBase::OnLoadGameButtonClicked);
    MainMenuButton->OnClicked.BindUObject(this, &UDeathScreenBase::OnMainMenuButtonClicked);
}

void UDeathScreenBase::RemoveDelegates()
{
    NewGameButton->OnClicked.Unbind();
    LoadGameButton->OnClicked.Unbind();
    MainMenuButton->OnClicked.Unbind();
}

void UDeathScreenBase::OnNewGameButtonClicked()
{
    if(GameInstance)
    {
        GameInstance->LoadGame = false;
        LoadMainLevel();
    }
}

void UDeathScreenBase::OnLoadGameButtonClicked()
{
    if(GameInstance)
    {
        GameInstance->LoadGame = true;
        LoadMainLevel();
    }
}


