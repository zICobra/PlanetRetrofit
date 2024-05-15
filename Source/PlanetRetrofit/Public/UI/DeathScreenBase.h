// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CommonActivatableWidgetBase.h"
#include "DeathScreenBase.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API UDeathScreenBase : public UCommonActivatableWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	void AddDelegates();
	void RemoveDelegates();



	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay;
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* VerticalBox;
	
	
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* NewGameButton;
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* LoadGameButton;
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* MainMenuButton;


	UPROPERTY()
	class UDefaultGameInstance* GameInstance = nullptr;

protected:
	UFUNCTION()
	void OnNewGameButtonClicked();
	UFUNCTION()
	void OnLoadGameButtonClicked();
	UFUNCTION(BlueprintImplementableEvent)
	void OnMainMenuButtonClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void LoadMainLevel();

	
};
