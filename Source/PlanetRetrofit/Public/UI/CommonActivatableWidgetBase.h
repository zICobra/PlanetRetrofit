// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonActivatableWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API UCommonActivatableWidgetBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
};
