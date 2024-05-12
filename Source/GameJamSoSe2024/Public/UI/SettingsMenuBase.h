// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CommonActivatableWidgetBase.h"
#include "SettingsMenuBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAMSOSE2024_API USettingsMenuBase : public UCommonActivatableWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct();

	UPROPERTY(meta = (BindWidget))
	class USliderBase* MasterSlider;
	UPROPERTY(meta = (BindWidget))
	class USliderBase* MusicSlider;
	UPROPERTY(meta = (BindWidget))
	class USliderBase* SFXSlider;
	UPROPERTY(meta = (BindWidget))
	class USliderBase* MouseSensSlider;
	UPROPERTY(meta = (BindWidget))
	class USliderBase* ControllerSensSlider;
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* BackButton;

	UPROPERTY()
	class UDefaultGameInstance* GameInstance;

	void SetUpSliderValue();
	void RemoveDelegates();
	
	void MasterSliderValueChanged(float NewValue);
	void MusicSliderValueChanged(float NewValue);
	void SFXSliderValueChanged(float NewValue);
	void MouseSensSliderValueChanged(float NewValue);
	void ControllerSensSliderValueChanged(float NewValue);

	void BackButtonCalled();


};
