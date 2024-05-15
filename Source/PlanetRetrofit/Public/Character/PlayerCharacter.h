// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagAssetInterface.h"
#include "Interfaces/GamplayTagsInterface.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class PLANETRETROFIT_API APlayerCharacter : public ACharacter, public IGameplayTagAssetInterface, public IGamplayTagsInterface
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint")
	float SprintSpeed = 800.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint")
	float WalkSpeed = 600.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interact")
	float InteractionRange = 1000.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Oxygen")
	float MaxHealth = 100.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Oxygen")
	float MaxOxygen = 100.0f;

	UPROPERTY()
	float CurrentHealth = MaxHealth;
	UPROPERTY()
	float CurrentOxygen = MaxOxygen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags")
	FGameplayTagContainer GameplayTags;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override 
	{ 
		TagContainer = GameplayTags; 
		return; 
	}

	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	int32 StoneAmountPerOreMined = 1;
	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	int32 IronAmountPerOreMined = 1;
	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	int32 CopperAmountPerOreMined = 1;
	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	int32 AmethystAmountPerOreMined = 1;
	UPROPERTY(EditDefaultsOnly, Category = "Mining")
	int32 PlatinAmountPerOreMined = 1;

	UPROPERTY()
	AActor* HitActor = nullptr;


	class IOutlineInterface* PreviouslyOutlinedActor = nullptr;
	class ABuildingInteractableBase* BuildingBase = nullptr;

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

	void StartJump();
	void StopJump();

	void StartSprint();
	void StopSprint();

	void ControllerSprint();

	void Interact();

	void PullUpMaterialUI();

	void Mine();

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
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UDeathScreenBase> DeathScreen;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UBuildingWidgetBase> BuildingWidget;
	
	UPROPERTY()	
	class UCommonUserWidgetBase* CreatedGameUIBase = nullptr;
	UPROPERTY()
	class UPauseMenuBase* CreatedPauseMenu = nullptr;
	UPROPERTY()
	class USettingsMenuBase* CreatedSettingsMenu = nullptr;
	UPROPERTY()	
	class UGamePlayWidgetBase* CreatedGamePlayMenu = nullptr;
	UPROPERTY()
	class UDeathScreenBase* CreatedDeathScreen = nullptr;
	UPROPERTY()
	class UBuildingWidgetBase* CreatedBuildingWidget = nullptr;

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

	FGameplayTag OxygenTag;

public:
	virtual void AddGameplayTag() override;
	virtual void RemoveGameplayTag() override;

private:
	void ShowBuildingMenu();
	UFUNCTION()
	void ClearBuildingMenu();
	UFUNCTION()
	void SpawnBuilding(int32 BuildingIndex);

};







