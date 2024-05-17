// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UpgradeWidgetBase.h"

#include "UI/ButtonBase.h"
#include "CommonTextBlock.h"

#include "DefaultGameInstance.h"
#include "SaveGame/DefaultSaveGame.h"

#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"


void UUpgradeWidgetBase::NativeConstruct()
{
    GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());

    if(GameInstance)
    {
        SetText();
    }
    UpgradeOxygenButton->SetFocus();

    UpgradeOxygenButton->OnClicked.BindUObject(this, &UUpgradeWidgetBase::OnUpgradeButtonClicked);
    BackButton->OnClicked.BindUObject(this, &UUpgradeWidgetBase::OnBackButtonClicked);
}

void UUpgradeWidgetBase::OnUpgradeButtonClicked()
{
    if(GameInstance->SaveGame->OxygenDepletionMultiplier == 4 && GameInstance->SaveGame->PlatinAmount >= 2)
    {
        GameInstance->SaveGame->OxygenDepletionMultiplier = 1.5;
        GameInstance->SaveGame->PlatinAmount -= 2; 
        SetText();
    }
    else if(GameInstance->SaveGame->OxygenDepletionMultiplier == 1.5 && GameInstance->SaveGame->PlatinAmount >= 4)
    {
        GameInstance->SaveGame->OxygenDepletionMultiplier = 0.2;
        GameInstance->SaveGame->PlatinAmount -= 4; 
        SetText();
    }
    else if(GameInstance->SaveGame->OxygenDepletionMultiplier == 0.2)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), FailedUpgradeSound);
    }
    else
    {
        UGameplayStatics::PlaySound2D(GetWorld(), FailedUpgradeSound);
    }
}

void UUpgradeWidgetBase::OnBackButtonClicked()
{
    UpgradeOxygenButton->OnClicked.Unbind();
    BackButton->OnClicked.Unbind();

    OnUpgradeUIBackButtonClicked.ExecuteIfBound();
}

void UUpgradeWidgetBase::SetText()
{
    if(GameInstance->SaveGame->OxygenDepletionMultiplier == 4)
        {
            if(GameInstance->SaveGame->PlatinAmount >= 2)
            {
                FString NewText = "2 more upgrades available.  Next upgrade cost: 2 Platin";
                UpgradePrice->SetText(FText::FromString(NewText));
                UpgradePrice->SetColorAndOpacity(FLinearColor::Green);
            }
            else
            {
                FString NewText = "2 more upgrades available.  Next upgrade cost: 2 Platin";
                UpgradePrice->SetText(FText::FromString(NewText));
                UpgradePrice->SetColorAndOpacity(FLinearColor::Red);
            }
        }
        else if(GameInstance->SaveGame->OxygenDepletionMultiplier == 1.5)
        {
            if(GameInstance->SaveGame->PlatinAmount >= 4)
            {
                FString NewText = "1 more upgrades available.  Next upgrade cost: 4 Platin";
                UpgradePrice->SetText(FText::FromString(NewText));
                UpgradePrice->SetColorAndOpacity(FLinearColor::Green);
            }
            else
            {
                FString NewText = "1 more upgrades available.  Next upgrade cost: 4 Platin";
                UpgradePrice->SetText(FText::FromString(NewText));
                UpgradePrice->SetColorAndOpacity(FLinearColor::Red);
            }

        }
        else if(GameInstance->SaveGame->OxygenDepletionMultiplier == 0.2)
        {
            FString NewText = FString::Printf(TEXT("No more available upgrades."));     
            UpgradePrice->SetText(FText::FromString(NewText));
        }
}
