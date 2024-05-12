// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SliderBase.h"



USliderBase::USliderBase()
{
    OnValueChanged.AddDynamic(this, &USliderBase::HandleOnValueChanged);
}

void USliderBase::HandleOnValueChanged(float InValue)
{
    OnSliderValueChanged.ExecuteIfBound(InValue);
}

