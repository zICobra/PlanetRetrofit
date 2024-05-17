// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Components/Overlay.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "MainMenuWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API UMainMenuWidgetBase : public UCommonUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay;

public:
	UPROPERTY(meta = (BindWidget))
	UCommonActivatableWidgetStack* ContentStack;

	UPROPERTY(EditDefaultsOnly)
	class USoundCue* BGMusic;

	void PushMainMenuUI(class UMainMenuUI* MainMenuUI);

	void PushSettingsMenu(class USettingsMenuBase* SettingsMenu);

};

