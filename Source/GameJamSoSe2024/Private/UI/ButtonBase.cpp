// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ButtonBase.h"

#include "Components/Overlay.h"
#include "CommonTextBlock.h"


void UButtonBase::NativePreConstruct()
{
    ButtonNameText->SetText(FText::FromString(ButtonText));
}

void UButtonBase::NativeOnClicked()
{
    OnClicked.ExecuteIfBound();
}


void UButtonBase::OverrideButtonText(FString NewButtonName)
{
    ButtonNameText->SetText(FText::FromString(NewButtonName));
}

