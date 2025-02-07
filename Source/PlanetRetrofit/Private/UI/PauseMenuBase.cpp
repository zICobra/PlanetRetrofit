// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenuBase.h"

#include "Components/Overlay.h"
#include "Components/VerticalBox.h"
#include "UI/ButtonBase.h"
#include "Components/Button.h"
#include "UI/CommonUserWidgetBase.h"

void UPauseMenuBase::NativeConstruct()
{
    ResumeButton->OnClicked.BindUObject(this, &UPauseMenuBase::OnResumeButtonClicked);
    SettingsButton->OnClicked.BindUObject(this, &UPauseMenuBase::OnSettingsButtonClicked);
    MainMenuButton->OnClicked.BindUObject(this, &UPauseMenuBase::OnMainMenuButtonClicked);
    ImStuckButton->OnClicked.BindUObject(this, &UPauseMenuBase::OnImStuckButtonClicked);
    if(HasOxygenTag)
    {
        ImStuckButton->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        ImStuckButton->SetVisibility(ESlateVisibility::Collapsed);
    }
    ResumeButton->SetFocus();
}

void UPauseMenuBase::RemoveDelegates()
{
    ResumeButton->OnClicked.Unbind();
    SettingsButton->OnClicked.Unbind();
    MainMenuButton->OnClicked.Unbind();
    ImStuckButton->OnClicked.Unbind();
}

void UPauseMenuBase::OnResumeButtonClicked()
{
    ResumButtonClickedDelagate.Broadcast();
}

void UPauseMenuBase::OnSettingsButtonClicked()
{
    SettingsButtonClickedDelegate.Broadcast();
}

void UPauseMenuBase::OnImStuckButtonClicked()
{
    ImStuckButtonClickedDelegate.Broadcast();
}



