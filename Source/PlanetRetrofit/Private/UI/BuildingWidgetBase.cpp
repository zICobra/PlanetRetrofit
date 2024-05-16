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
        SetText();

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

    HappyFieldButton->OnHovered.BindUObject(this, &UBuildingWidgetBase::HappyFieldButtonSelected);
    SaladFieldButton->OnHovered.BindUObject(this, &UBuildingWidgetBase::SaladFieldButtonSelected);
    CarrotFieldButton->OnHovered.BindUObject(this, &UBuildingWidgetBase::CarrotFieldButtonSelected);
}

void UBuildingWidgetBase::RemoveDelegates()
{
    BackButton->OnClicked.Unbind();
    BuildButton->OnClicked.Unbind();

    HappyFieldButton->OnClicked.Unbind();
    SaladFieldButton->OnClicked.Unbind();
    CarrotFieldButton->OnClicked.Unbind();

    HappyFieldButton->OnHovered.Unbind();
    SaladFieldButton->OnHovered.Unbind();
    CarrotFieldButton->OnHovered.Unbind();
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
    RemoveMaterials();
    DeactivateWidget();
}

void UBuildingWidgetBase::OnHappyPlantFieldButtonClicked()
{
    RemoveDelegates();
    OnBuildButtonClicked.ExecuteIfBound(BuildingIndex);
    RemoveMaterials();
    DeactivateWidget();
}

void UBuildingWidgetBase::OnSaladFieldButtonClicked()
{
    RemoveDelegates();
    OnBuildButtonClicked.ExecuteIfBound(BuildingIndex);
    RemoveMaterials();
    DeactivateWidget();
}

void UBuildingWidgetBase::OnCarrotFieldButtonClicked()
{
    RemoveDelegates();
    OnBuildButtonClicked.ExecuteIfBound(BuildingIndex);
    RemoveMaterials();
    DeactivateWidget();
}




void UBuildingWidgetBase::HappyFieldButtonSelected()
{
    if(IsFarm1)
    {
        BuildingIndex = 1;
    }
    else if(IsFarm2)
    {
        BuildingIndex = 4;
    }
    else if(IsFarm3)
    {
        BuildingIndex = 7;
    }
    else if(IsFarm4)
    {
        BuildingIndex = 10;
    }
    SetText();
}

void UBuildingWidgetBase::SaladFieldButtonSelected()
{
    if(IsFarm1)
    {
        BuildingIndex = 2;
    }
    else if(IsFarm2)
    {
        BuildingIndex = 5;
    }
    else if(IsFarm3)
    {
        BuildingIndex = 8;
    }
    else if(IsFarm4)
    {
        BuildingIndex = 11;
    }
    SetText();
}

void UBuildingWidgetBase::CarrotFieldButtonSelected()
{   
    if(IsFarm1)
    {
        BuildingIndex = 3;
    }
    else if(IsFarm2)
    {
        BuildingIndex = 6;
    }
    else if(IsFarm3)
    {
        BuildingIndex = 9;
    }
    else if(IsFarm4)
    {
        BuildingIndex = 12;
    }
    SetText();
}




void UBuildingWidgetBase::SetText()
{
    UE_LOG(LogTemp, Warning, TEXT("%d"), BuildingIndex);
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


void UBuildingWidgetBase::RemoveMaterials()
{
    if(GameInstance)
    {
        GameInstance->SaveGame->StoneAmount -= GameInstance->BuildingConfig->Buildings[BuildingIndex].StoneAmount;
        GameInstance->SaveGame->IronAmount -= GameInstance->BuildingConfig->Buildings[BuildingIndex].IronAmount;
        GameInstance->SaveGame->CopperAmount -= GameInstance->BuildingConfig->Buildings[BuildingIndex].CopperAmount;
        GameInstance->SaveGame->AmethystAmount -= GameInstance->BuildingConfig->Buildings[BuildingIndex].AmethystAmount;
        GameInstance->SaveGame->PlatinAmount -= GameInstance->BuildingConfig->Buildings[BuildingIndex].PlatinAmount;
    }
}
