// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagAssetInterface.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class GAMEJAMSOSE2024_API APlayerCharacter : public ACharacter, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void RestartLevel();

#pragma region Variables


	FInputModeGameAndUI GameAndUIInputMode;
	FInputModeGameOnly GameOnlyInputMode;
	FInputModeUIOnly UIOnlyInputMode;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags")
	FGameplayTagContainer GameplayTags;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override 
	{ 
		TagContainer = GameplayTags; 
		return; 
	}


#pragma endregion Variables



#pragma region Inputs

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputConfig* InputActions;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

private:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
	void LookController(const FInputActionValue& Value);

	UFUNCTION()
	void CallPauseMenu();
	UFUNCTION()
	void CallSettingsMenu();

#pragma endregion Inputs

#pragma region Components

protected:

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

#pragma endregion Components

#pragma region UI

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UCommonUserWidgetBase> GameUIBase;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UCommonActivatableWidgetBase> PauseMenu;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UCommonActivatableWidgetBase> SettingsMenu;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UGamePlayWidgetBase> GamePlayUI;
	
	UPROPERTY()	
	class UCommonUserWidgetBase* CreatedGameUIBase = nullptr;
	UPROPERTY()
	class UPauseMenuBase* CreatedPauseMenu = nullptr;
	UPROPERTY()
	class USettingsMenuBase* CreatedSettingsMenu = nullptr;
	UPROPERTY()	
	class UGamePlayWidgetBase* CreatedGamePlayMenu = nullptr;

#pragma endregion UI

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	AActor* TargetToFocus = nullptr;

	APlayerController* ActivePlayerController = nullptr;
	ACharacter* PlayerCharacter = nullptr;

	UPROPERTY()
	class UDefaultGameInstance* GameInstance = nullptr;

	UGameplayTagsManager& GetGameplayTagsManager();

};







