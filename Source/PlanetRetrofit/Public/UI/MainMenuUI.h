// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CommonActivatableWidgetBase.h"
#include "MainMenuUI.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSettingsButtonPressed);

UCLASS()
class PLANETRETROFIT_API UMainMenuUI : public UCommonActivatableWidgetBase
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	void AddDelegates();
	void RemoveDelegates();

	UFUNCTION(BlueprintImplementableEvent)
	void LoadMainLevel();

	UPROPERTY()
	class UDefaultGameInstance* GameInstance = nullptr;

#pragma region Variables

	bool FirstSaveButtonIsLoadGame = false;
	bool SecondSaveButtonIsLoadGame = false;
	bool ThirdSaveButtonIsLoadGame = false;

#pragma endregion Variables


#pragma region Components

protected:

	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay;
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* ButtonVerticalBox;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCommonTextBlock* NewGameWarning;

#pragma region Components




#pragma region Buttons

protected:
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* BP_NewGameButton;
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* BP_LoadGameButton;
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* BP_SettingsButton;
	UPROPERTY(meta = (BindWidget))
	class UButtonBase* BP_ExitButton;


#pragma endregion Buttons




#pragma region Functions

protected:
	UFUNCTION(BlueprintCallable)
	void OnNewGameButtonClicked();
	UFUNCTION(BlueprintCallable)
	void OnLoadGameButtonClicked();
	UFUNCTION(BlueprintCallable)
	void OnSettingsButtonClicked();
	UFUNCTION(BlueprintCallable)
	void OnExitButtonClicked();

	UFUNCTION()
	void OnNewGameButtonHovered();
	UFUNCTION(BlueprintCallable)
	void OnNewGameButtonUnHovered();


#pragma endregion Functions

public:
	FSettingsButtonPressed SettingsButtonPressedDelegate;

};





