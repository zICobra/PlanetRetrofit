// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BuildingWidgetBase.h"

#include "UI/ButtonBase.h"
#include "Components/VerticalBox.h"
#include "CommonTextBlock.h"

#include "DataAssets/BuildingsConfig.h"

#include "DefaultGameInstance.h"
#include "SaveGame/DefaultSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UBuildingWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());

    if(GameInstance->BuildingConfig && GameInstance->BuildingConfig->Buildings.Num() > BuildingIndex)
    {
        BuildingName->SetText(FText::FromString(GameInstance->BuildingConfig->Buildings[BuildingIndex].BuildingName));

        if(GameInstance->BuildingConfig->Buildings[BuildingIndex].StoneAmount >= GameInstance->SaveGame->StoneAmount)
        {
            FString NewText = FString::Printf(TEXT("Stone needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].StoneAmount);
            StoneAmountNeeded->SetText(FText::FromString(NewText));
            // StoneAmountNeeded->SetColor(FLinearColor::Green);
        }
        else
        {
            FString NewText = FString::Printf(TEXT("Stone needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].StoneAmount);
            StoneAmountNeeded->SetText(FText::FromString(NewText));
            // StoneAmountNeeded->SetColor(FLinearColor::Red);
        }
        if(GameInstance->BuildingConfig->Buildings[BuildingIndex].IronAmount >= GameInstance->SaveGame->IronAmount)
        {
            FString NewText = FString::Printf(TEXT("Iron needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].IronAmount);
            IronAmountNeeded->SetText(FText::FromString(NewText));
            // IronAmountNeeded->SetColor(FLinearColor::Green);
        }
        else
        {
            FString NewText = FString::Printf(TEXT("Iron needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].IronAmount);
            IronAmountNeeded->SetText(FText::FromString(NewText));
            // IronAmountNeeded->SetColor(FLinearColor::Red);
        }
        if(GameInstance->BuildingConfig->Buildings[BuildingIndex].CopperAmount >= GameInstance->SaveGame->CopperAmount)
        {
            FString NewText = FString::Printf(TEXT("Copper needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].CopperAmount);
            CopperAmountNeeded->SetText(FText::FromString(NewText));
            // CopperAmountNeeded->SetColor(FLinearColor::Green);
        }
        else
        {
            FString NewText = FString::Printf(TEXT("Copper needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].CopperAmount);
            CopperAmountNeeded->SetText(FText::FromString(NewText));
            // CopperAmountNeeded->SetColor(FLinearColor::Red);
        }
        if(GameInstance->BuildingConfig->Buildings[BuildingIndex].AmethystAmount >= GameInstance->SaveGame->AmethystAmount)
        {
            FString NewText = FString::Printf(TEXT("Amethyst needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].AmethystAmount);
            AmethystAmountNeeded->SetText(FText::FromString(NewText));
            // AmethystAmountNeeded->SetColor(FLinearColor::Green);
        }
        else
        {
            FString NewText = FString::Printf(TEXT("Amethyst needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].AmethystAmount);
            AmethystAmountNeeded->SetText(FText::FromString(NewText));
            // AmethystAmountNeeded->SetColor(FLinearColor::Red);
        }
        if(GameInstance->BuildingConfig->Buildings[BuildingIndex].PlatinAmount >= GameInstance->SaveGame->PlatinAmount)
        {
            FString NewText = FString::Printf(TEXT("Platin needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].PlatinAmount);
            PlatinAmountNeeded->SetText(FText::FromString(NewText));
            // PlatinAmountNeeded->SetColor(FLinearColor::Green);
        }
        else
        {
            FString NewText = FString::Printf(TEXT("Platin needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].PlatinAmount);
            PlatinAmountNeeded->SetText(FText::FromString(NewText));
            // PlatinAmountNeeded->SetColor(FLinearColor::Red);
        }
    }

    BackButton->SetFocus();
    AddDelegates();
}

void UBuildingWidgetBase::AddDelegates()
{
    BackButton->OnClicked.BindUObject(this, &UBuildingWidgetBase::OnBackButtonClickedFunction);
    BuildButton->OnClicked.BindUObject(this, &UBuildingWidgetBase::OnBuildButtonClickedFunction);
}

void UBuildingWidgetBase::RemoveDelegates()
{
    BackButton->OnClicked.Unbind();
    BuildButton->OnClicked.Unbind();
}

void UBuildingWidgetBase::OnBackButtonClickedFunction()
{
    RemoveDelegates();
    OnBackButtonClicked.ExecuteIfBound();
}

void UBuildingWidgetBase::OnBuildButtonClickedFunction()
{
    RemoveDelegates();
    OnBuildButtonClicked.ExecuteIfBound();
}
