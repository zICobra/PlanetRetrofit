// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CommonActivatableWidgetBase.h"
#include "BuildingWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API UBuildingWidgetBase : public UCommonActivatableWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	void AddDelegates();
	void RemoveDelegates();


	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* BuildingName;
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* StoneAmountNeeded;
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* IronAmountNeeded;
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* CopperAmountNeeded;
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* AmethystAmountNeeded;
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* PlatinAmountNeeded;


	UPROPERTY(meta = (BindWidget))
	class UButtonBase* BackButton;
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* BuildButton;



	UPROPERTY()
	class UDefaultGameInstance* GameInstance = nullptr;
public:
	UPROPERTY()
	int32 BuildingIndex = 0;
	UPROPERTY()
	bool IsFarm = false;

	DECLARE_DELEGATE(FOnBackButtonClicked);
	DECLARE_DELEGATE(FOnBuildButtonClicked);

	FOnBackButtonClicked OnBackButtonClicked;
	FOnBuildButtonClicked OnBuildButtonClicked;


protected:
	UFUNCTION()
	void OnBackButtonClickedFunction();
	UFUNCTION()
	void OnBuildButtonClickedFunction();
	
};
