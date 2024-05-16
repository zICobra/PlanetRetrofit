// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CommonActivatableWidgetBase.h"
#include "UpgradeWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API UUpgradeWidgetBase : public UCommonActivatableWidgetBase
{
	GENERATED_BODY()
	

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButtonBase* UpgradeOxygenButton;
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* BackButton;

	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* UpgradePrice;


	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundCue* FailedUpgradeSound;



	UPROPERTY()
	class UDefaultGameInstance* GameInstance = nullptr;


	UFUNCTION()
	void OnUpgradeButtonClicked();
	UFUNCTION()
	void OnBackButtonClicked();

	void SetText();

public:

	DECLARE_DELEGATE(FOnBackButtonClicked)

	FOnBackButtonClicked OnUpgradeUIBackButtonClicked;
};
