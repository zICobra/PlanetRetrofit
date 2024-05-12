// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Components/Overlay.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "CommonUserWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAMSOSE2024_API UCommonUserWidgetBase : public UCommonUserWidget
{
	GENERATED_BODY()


protected:
	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay;

public:
	UPROPERTY(meta = (BindWidget))
	UCommonActivatableWidgetStack* GameplayStack;
	UPROPERTY(meta = (BindWidget))
	UCommonActivatableWidgetStack* PauseMenuStack;


	void PushGamePlayMenu(class UCommonActivatableWidgetBase* GamePlayMenu);

	void PushPauseMenu(class UCommonActivatableWidgetBase* PauseMenu);
	void ClearPauseMenu();

	void PushSettingsMenu(class UCommonActivatableWidgetBase* SettingsMenu);
	void ClearSettingsMenu();
	
	bool PauseMenuActive = false;
	
};
