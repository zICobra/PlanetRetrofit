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

	UPROPERTY(meta = (BindWidget))
	class UOverlay* MaterialOverlay;
	UPROPERTY(meta = (BindWidget))
	class UCommonLazyImage* PhoneImage;
	UPROPERTY(meta = (BindWidget))
	class UCommonLazyImage* StoneImage;
	UPROPERTY(meta = (BindWidget))
	class UCommonLazyImage* IronImage;
	UPROPERTY(meta = (BindWidget))
	class UCommonLazyImage* CopperImage;
	UPROPERTY(meta = (BindWidget))
	class UCommonLazyImage* AmethystImage;
	UPROPERTY(meta = (BindWidget))
	class UCommonLazyImage* PlatinImage;

	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* StoneAmountText;
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* IronAmountText;
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* CopperAmountText;
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* AmethystAmountText;
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* PlatinAmountText;

public:

	virtual void NativeConstruct() override;

	UPROPERTY()
	class UDefaultGameInstance* GameInstance = nullptr;
	
	bool MaterialUIIsActive = false;

	void PullUpMaterialUI(const int32 StoneAmount, const int32 IronAmount, const int32 CopperAmount, const int32 AmethystAmount, const int32 PlatinAmount);

	void RemoveMaterialUI();
private:


};
