// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GamePlayWidgetBase.h"

#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialInstance.h"
#include "DefaultGameInstance.h"

#include "Components/Overlay.h"
#include "CommonLazyImage.h"
#include "CommonTextBlock.h"
#include "Components/ProgressBar.h"

void UGamePlayWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());

}

void UGamePlayWidgetBase::PullUpMaterialUI(const int32 StoneAmount, const int32 IronAmount, const int32 CopperAmount, const int32 AmethystAmount, const int32 PlatinAmount)
{
    MaterialOverlay->SetVisibility(ESlateVisibility::Visible);

    MaterialUIIsActive = true;

    FString StoneText = FString::Printf(TEXT("%d"), StoneAmount);
    FString IronText = FString::Printf(TEXT("%d"), IronAmount);
    FString CopperText = FString::Printf(TEXT("%d"), CopperAmount);
    FString AmethystText = FString::Printf(TEXT("%d"), AmethystAmount);
    FString PlatinText = FString::Printf(TEXT("%d"), PlatinAmount);

    StoneAmountText->SetText(FText::FromString(StoneText));
    IronAmountText->SetText(FText::FromString(IronText));
    CopperAmountText->SetText(FText::FromString(CopperText));
    AmethystAmountText->SetText(FText::FromString(AmethystText));
    PlatinAmountText->SetText(FText::FromString(PlatinText));
}

void UGamePlayWidgetBase::RemoveMaterialUI()
{
    MaterialOverlay->SetVisibility(ESlateVisibility::Collapsed);

    MaterialUIIsActive = false;
}

void UGamePlayWidgetBase::SetOxygenBar(const float MaxOxygen, const float CurrentOxygen)
{
    OxygenBar->SetPercent(CurrentOxygen / MaxOxygen);
}

void UGamePlayWidgetBase::SetHealthBar(const float MaxHealth, const float CurrentHealth)
{
    HealthBar->SetPercent(CurrentHealth / MaxHealth);
}

