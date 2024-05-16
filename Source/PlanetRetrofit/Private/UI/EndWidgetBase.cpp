// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EndWidgetBase.h"

#include "UI/ButtonBase.h"


void UEndWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();


    MainMenuButton->OnClicked.BindUObject(this, &UEndWidgetBase::OnMainButtonClicked);

    MainMenuButton->SetFocus();

}

void UEndWidgetBase::RemoveDelegate()
{
    MainMenuButton->OnClicked.Unbind();
}

