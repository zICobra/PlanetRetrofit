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
	
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* HappyFieldButton;
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* SaladButton;
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* CarrotFieldButton;



	UPROPERTY()
	class UDefaultGameInstance* GameInstance = nullptr;
public:
	UPROPERTY()
	int32 BuildingIndex = 0;
	UPROPERTY()
	int32 FieldSelectionIndex = 1;
	UPROPERTY()
	bool IsFarm = false;

	DECLARE_DELEGATE(FOnBackButtonClicked);
	DECLARE_DELEGATE_OneParam(FOnBuildButtonClicked, int32 BuildingIndex);

	FOnBackButtonClicked OnBackButtonClicked;
	FOnBuildButtonClicked OnBuildButtonClicked;


protected:
	UFUNCTION()
	void OnBackButtonClickedFunction();
	UFUNCTION()
	void OnBuildButtonClickedFunction();
	UFUNCTION()
	void OnHappyPlantFieldButtonClicked();
	UFUNCTION()
	void OnSaladFieldButtonClicked();
	UFUNCTION()
	void OnCarrotFieldButtonClicked();

	UFUNCTION(BlueprintCallable)
	void HappyFieldButtonSelected();
	UFUNCTION(BlueprintCallable)
	void SaladFieldButtonSelected();
	UFUNCTION(BlueprintCallable)
	void CarrotFieldButtonSelected();

	void SetText();
	void SetTextForField();

private:
	bool EnoughtStone = false;
	bool EnoughtIron = false;
	bool EnoughtCopper = false;
	bool EnoughtAmethyst = false;
	bool EnoughtPlatin = false;
	
};
