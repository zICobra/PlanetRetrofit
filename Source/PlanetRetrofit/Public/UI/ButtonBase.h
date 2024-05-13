// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "ButtonBase.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API UButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeOnClicked() override;


	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay;
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* ButtonNameText;

public:
	UPROPERTY(EditAnywhere, Category = "Text")
	FString ButtonText = "Default";

	DECLARE_DELEGATE(FOnClicked);

	FOnClicked OnClicked;

	void OverrideButtonText(FString NewButtonName);
};
