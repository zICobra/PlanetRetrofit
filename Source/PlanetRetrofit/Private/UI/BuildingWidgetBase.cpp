// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BuildingWidgetBase.h"

#include "UI/ButtonBase.h"
#include "Components/VerticalBox.h"
#include "CommonTextBlock.h"

#include "DefaultGameInstance.h"
#include "SaveGame/DefaultSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UBuildingWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());

    BackButton->SetFocus();
    AddDelegate();
}

void UBuildingWidgetBase::AddDelegates()
{
    BackButton->OnClicked.BindUObject(this, &UBuildingWidgetBase::OnBackButtonClicked);
    BuildButton->OnClicked.BindUObject(this, &UBuildingWidgetBase::OnBuildButtonClicked);
}

void UBuildingWidgetBase::RemoveDelegates()
{
    BackButton->OnClicked.Unbind();
    BuildButton->OnClicked.Unbind();
}

void UBuildingWidgetBase::OnBackButtonClicked()
{
    RemoveDelegates();
    OnBackButtonClicked.ExecuteIfBound();
}

void UBuildingWidgetBase::OnBuildButtonClicked()
{
    OnBuildButtonClicked.ExecuteIfBound();
    //TODO: SpawnBuilding
}
