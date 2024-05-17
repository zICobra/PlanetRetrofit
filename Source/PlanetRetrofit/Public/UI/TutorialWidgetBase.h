// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CommonActivatableWidgetBase.h"
#include "TutorialWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API UTutorialWidgetBase : public UCommonActivatableWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButtonBase* PlayButton;

	UFUNCTION()
	void OnPLayButtonClicked();
	

public:
	DECLARE_DELEGATE(FOnTutorialPlayButtonClicked);

	FOnTutorialPlayButtonClicked OnTutorialPlayButtonClicked;
};
