// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TutorialWidgetBase.h"

#include "UI/ButtonBase.h"

void UTutorialWidgetBase::NativeConstruct()
{
    PlayButton->OnClicked.BindUObject(this, &UTutorialWidgetBase::OnPLayButtonClicked);
    
    PlayButton->SetFocus();
}


void UTutorialWidgetBase::OnPLayButtonClicked()
{
    PlayButton->OnClicked.Unbind();
    OnTutorialPlayButtonClicked.ExecuteIfBound();
}

