// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CommonActivatableWidgetBase.h"
#include "EndWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API UEndWidgetBase : public UCommonActivatableWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct();

	UPROPERTY(meta = (BindWidget))
	class UButtonBase* MainMenuButton;

	UFUNCTION(BlueprintImplementableEvent)
	void OnMainButtonClicked();
	UFUNCTION(BlueprintCallable)
	void RemoveDelegate();
};
