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
	virtual void NativeOnHovered() override;


	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay;
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* ButtonNameText;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundCue* HoverSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundCue* ClickSound;

public:
	UPROPERTY(EditAnywhere, Category = "Text")
	FString ButtonText = "Default";

	DECLARE_DELEGATE(FOnClicked);
	DECLARE_DELEGATE(FOnHovered);

	FOnClicked OnClicked;
	FOnHovered OnHovered;

	void OverrideButtonText(FString NewButtonName);
};
