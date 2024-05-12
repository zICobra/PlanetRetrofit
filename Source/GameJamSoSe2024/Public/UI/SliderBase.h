// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Slider.h"
#include "SliderBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAMSOSE2024_API USliderBase : public USlider
{
	GENERATED_BODY()

protected:
	USliderBase();

	UFUNCTION()
	virtual void HandleOnValueChanged(float InValue);

public:
	DECLARE_DELEGATE_OneParam(FOnSliderValueChangedDelegate, float InValue);

	FOnSliderValueChangedDelegate OnSliderValueChanged;
	
};
