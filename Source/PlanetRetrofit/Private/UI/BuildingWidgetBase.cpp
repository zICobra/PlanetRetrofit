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

    FieldSelectionIndex = 1;

    if(GameInstance->BuildingConfig && GameInstance->BuildingConfig->Buildings.Num() > BuildingIndex)
    {
        if(IsFarm)
        {
            SetTextForField();
        }
        else
        {
            SetText();
        }

        if(EnoughtStone && EnoughtIron && EnoughtCopper && EnoughtAmethyst && EnoughtPlatin)
        {
            BuildButton->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            BuildButton->SetVisibility(ESlateVisibility::Collapsed);
        }
    }

    if(IsFarm)
    {
        HappyFieldButton->SetVisibility(ESlateVisibility::Visible);
        SaladFieldButton->SetVisibility(ESlateVisibility::Visible);
        CarrotFieldButton->SetVisibility(ESlateVisibility::Visible);

        HappyFieldButton->SetFocus();
        BuildButton->SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        HappyFieldButton->SetVisibility(ESlateVisibility::Collapsed);
        SaladFieldButton->SetVisibility(ESlateVisibility::Collapsed);
        CarrotFieldButton->SetVisibility(ESlateVisibility::Collapsed);

        BackButton->SetFocus();
    }

    AddDelegates();
}

void UBuildingWidgetBase::AddDelegates()
{
    BackButton->OnClicked.BindUObject(this, &UBuildingWidgetBase::OnBackButtonClickedFunction);
    BuildButton->OnClicked.BindUObject(this, &UBuildingWidgetBase::OnBuildButtonClickedFunction);

    HappyFieldButton->OnClicked.BindUObject(this, &UBuildingWidgetBase::OnHappyPlantFieldButtonClicked);
    SaladFieldButton->OnClicked.BindUObject(this, &UBuildingWidgetBase::OnSaladFieldButtonClicked);
    CarrotFieldButton->OnClicked.BindUObject(this, &UBuildingWidgetBase::OnCarrotFieldButtonClicked);
}

void UBuildingWidgetBase::RemoveDelegates()
{
    BackButton->OnClicked.Unbind();
    BuildButton->OnClicked.Unbind();

    HappyFieldButton->OnClicked.Unbind();
    SaladFieldButton->OnClicked.Unbind();
    CarrotFieldButton->OnClicked.Unbind();
}




void UBuildingWidgetBase::OnBackButtonClickedFunction()
{
    RemoveDelegates();
    OnBackButtonClicked.ExecuteIfBound();
}

void UBuildingWidgetBase::OnBuildButtonClickedFunction()
{
    RemoveDelegates();
    OnBuildButtonClicked.ExecuteIfBound(BuildingIndex);
    DeactivateWidget();
}

void UBuildingWidgetBase::OnHappyPlantFieldButtonClicked()
{
    RemoveDelegates();
    OnBuildButtonClicked.ExecuteIfBound(FieldSelectionIndex);
    DeactivateWidget();
}

void UBuildingWidgetBase::OnSaladFieldButtonClicked()
{
    RemoveDelegates();
    OnBuildButtonClicked.ExecuteIfBound(FieldSelectionIndex);
    DeactivateWidget();
}

void UBuildingWidgetBase::OnCarrotFieldButtonClicked()
{
    RemoveDelegates();
    OnBuildButtonClicked.ExecuteIfBound(FieldSelectionIndex);
    DeactivateWidget();
}




void UBuildingWidgetBase::HappyFieldButtonSelected()
{
    FieldSelectionIndex = 1;
    SetTextForField();
}

void UBuildingWidgetBase::SaladFieldButtonSelected()
{
    FieldSelectionIndex = 2;
    SetTextForField();
}

void UBuildingWidgetBase::CarrotFieldButtonSelected()
{
    FieldSelectionIndex = 3;
    SetTextForField();
}




void UBuildingWidgetBase::SetText()
{
    BuildingName->SetText(FText::FromString(GameInstance->BuildingConfig->Buildings[BuildingIndex].BuildingName));

    if(GameInstance->BuildingConfig->Buildings[BuildingIndex].StoneAmount <= GameInstance->SaveGame->StoneAmount)
    {
        FString NewText = FString::Printf(TEXT("Stone needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].StoneAmount);
        StoneAmountNeeded->SetText(FText::FromString(NewText));
        StoneAmountNeeded->SetColorAndOpacity(FLinearColor::Green);
        EnoughtStone = true;
    }
    else
    {
        FString NewText = FString::Printf(TEXT("Stone needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].StoneAmount);
        StoneAmountNeeded->SetText(FText::FromString(NewText));
        StoneAmountNeeded->SetColorAndOpacity(FLinearColor::Red);
        EnoughtStone = false;
    }
    if(GameInstance->BuildingConfig->Buildings[BuildingIndex].IronAmount <= GameInstance->SaveGame->IronAmount)
    {
        FString NewText = FString::Printf(TEXT("Iron needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].IronAmount);
        IronAmountNeeded->SetText(FText::FromString(NewText));
        IronAmountNeeded->SetColorAndOpacity(FLinearColor::Green);
        EnoughtIron = true;
    }
    else
    {
        FString NewText = FString::Printf(TEXT("Iron needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].IronAmount);
        IronAmountNeeded->SetText(FText::FromString(NewText));
        IronAmountNeeded->SetColorAndOpacity(FLinearColor::Red);
        EnoughtIron = false;
    }
    if(GameInstance->BuildingConfig->Buildings[BuildingIndex].CopperAmount <= GameInstance->SaveGame->CopperAmount)
    {
        FString NewText = FString::Printf(TEXT("Copper needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].CopperAmount);
        CopperAmountNeeded->SetText(FText::FromString(NewText));
        CopperAmountNeeded->SetColorAndOpacity(FLinearColor::Green);
        EnoughtCopper = true;
    }
    else
    {
        FString NewText = FString::Printf(TEXT("Copper needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].CopperAmount);
        CopperAmountNeeded->SetText(FText::FromString(NewText));
        CopperAmountNeeded->SetColorAndOpacity(FLinearColor::Red);
        EnoughtCopper = false;
    }
    if(GameInstance->BuildingConfig->Buildings[BuildingIndex].AmethystAmount <= GameInstance->SaveGame->AmethystAmount)
    {
        FString NewText = FString::Printf(TEXT("Amethyst needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].AmethystAmount);
        AmethystAmountNeeded->SetText(FText::FromString(NewText));
        AmethystAmountNeeded->SetColorAndOpacity(FLinearColor::Green);
        EnoughtAmethyst = true;
    }
    else
    {
        FString NewText = FString::Printf(TEXT("Amethyst needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].AmethystAmount);
        AmethystAmountNeeded->SetText(FText::FromString(NewText));
        AmethystAmountNeeded->SetColorAndOpacity(FLinearColor::Red);
        EnoughtAmethyst = false;
    }
    if(GameInstance->BuildingConfig->Buildings[BuildingIndex].PlatinAmount <= GameInstance->SaveGame->PlatinAmount)
    {
        FString NewText = FString::Printf(TEXT("Platin needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].PlatinAmount);
        PlatinAmountNeeded->SetText(FText::FromString(NewText));
        PlatinAmountNeeded->SetColorAndOpacity(FLinearColor::Green);
        EnoughtPlatin = true;
    }
    else
    {
        FString NewText = FString::Printf(TEXT("Platin needed: %d"), GameInstance->BuildingConfig->Buildings[BuildingIndex].PlatinAmount);
        PlatinAmountNeeded->SetText(FText::FromString(NewText));
        PlatinAmountNeeded->SetColorAndOpacity(FLinearColor::Red);
        EnoughtPlatin = false;
    }
}



void UBuildingWidgetBase::SetTextForField()
{
    BuildingName->SetText(FText::FromString(GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].BuildingName));

    if(GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].StoneAmount <= GameInstance->SaveGame->StoneAmount)
    {
        FString NewText = FString::Printf(TEXT("Stone needed: %d"), GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].StoneAmount);
        StoneAmountNeeded->SetText(FText::FromString(NewText));
        StoneAmountNeeded->SetColorAndOpacity(FLinearColor::Green);
        EnoughtStone = true;
    }
    else
    {
        FString NewText = FString::Printf(TEXT("Stone needed: %d"), GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].StoneAmount);
        StoneAmountNeeded->SetText(FText::FromString(NewText));
        StoneAmountNeeded->SetColorAndOpacity(FLinearColor::Red);
        EnoughtStone = false;
    }
    if(GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].IronAmount <= GameInstance->SaveGame->IronAmount)
    {
        FString NewText = FString::Printf(TEXT("Iron needed: %d"), GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].IronAmount);
        IronAmountNeeded->SetText(FText::FromString(NewText));
        IronAmountNeeded->SetColorAndOpacity(FLinearColor::Green);
        EnoughtIron = true;
    }
    else
    {
        FString NewText = FString::Printf(TEXT("Iron needed: %d"), GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].IronAmount);
        IronAmountNeeded->SetText(FText::FromString(NewText));
        IronAmountNeeded->SetColorAndOpacity(FLinearColor::Red);
        EnoughtIron = false;
    }
    if(GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].CopperAmount <= GameInstance->SaveGame->CopperAmount)
    {
        FString NewText = FString::Printf(TEXT("Copper needed: %d"), GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].CopperAmount);
        CopperAmountNeeded->SetText(FText::FromString(NewText));
        CopperAmountNeeded->SetColorAndOpacity(FLinearColor::Green);
        EnoughtCopper = true;
    }
    else
    {
        FString NewText = FString::Printf(TEXT("Copper needed: %d"), GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].CopperAmount);
        CopperAmountNeeded->SetText(FText::FromString(NewText));
        CopperAmountNeeded->SetColorAndOpacity(FLinearColor::Red);
        EnoughtCopper = false;
    }
    if(GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].AmethystAmount <= GameInstance->SaveGame->AmethystAmount)
    {
        FString NewText = FString::Printf(TEXT("Amethyst needed: %d"), GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].AmethystAmount);
        AmethystAmountNeeded->SetText(FText::FromString(NewText));
        AmethystAmountNeeded->SetColorAndOpacity(FLinearColor::Green);
        EnoughtAmethyst = true;
    }
    else
    {
        FString NewText = FString::Printf(TEXT("Amethyst needed: %d"), GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].AmethystAmount);
        AmethystAmountNeeded->SetText(FText::FromString(NewText));
        AmethystAmountNeeded->SetColorAndOpacity(FLinearColor::Red);
        EnoughtAmethyst = false;
    }
    if(GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].PlatinAmount <= GameInstance->SaveGame->PlatinAmount)
    {
        FString NewText = FString::Printf(TEXT("Platin needed: %d"), GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].PlatinAmount);
        PlatinAmountNeeded->SetText(FText::FromString(NewText));
        PlatinAmountNeeded->SetColorAndOpacity(FLinearColor::Green);
        EnoughtPlatin = true;
    }
    else
    {
        FString NewText = FString::Printf(TEXT("Platin needed: %d"), GameInstance->BuildingConfig->Buildings[FieldSelectionIndex].PlatinAmount);
        PlatinAmountNeeded->SetText(FText::FromString(NewText));
        PlatinAmountNeeded->SetColorAndOpacity(FLinearColor::Red);
        EnoughtPlatin = false;
    }
}
