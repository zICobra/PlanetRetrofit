// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CommonActivatableWidgetBase.h"

#include "GamePlayWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API UGamePlayWidgetBase : public UCommonActivatableWidgetBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay;

public:

	virtual void NativeConstruct() override;

	UPROPERTY()
	class UDefaultGameInstance* GameInstance = nullptr;

private:


};
