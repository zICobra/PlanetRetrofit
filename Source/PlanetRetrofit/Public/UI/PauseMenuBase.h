// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CommonActivatableWidgetBase.h"
#include "PauseMenuBase.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResumeButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSettingsButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FImStuckButtonClicked);

UCLASS()
class PLANETRETROFIT_API UPauseMenuBase : public UCommonActivatableWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay;
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* VerticalBox;

	UPROPERTY(meta = (BindWidget))
	class UButtonBase* ResumeButton;
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* SettingsButton;
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* MainMenuButton;
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* ImStuckButton;

	void NativeConstruct() override;
	void RemoveDelegates();

	UFUNCTION()
	void OnResumeButtonClicked();
	UFUNCTION()
	void OnSettingsButtonClicked();
	UFUNCTION(BlueprintImplementableEvent)
	void OnMainMenuButtonClicked();
	UFUNCTION()
	void OnImStuckButtonClicked();


public:
	FResumeButtonClicked ResumButtonClickedDelagate;
	FSettingsButtonClicked SettingsButtonClickedDelegate;
	FImStuckButtonClicked ImStuckButtonClickedDelegate;

	bool HasOxygenTag = false;
};
