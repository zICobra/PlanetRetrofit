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
	void CameraAnimation();

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float HeadMovementIntensity = 4.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	class USoundCue* DeathSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	class USoundCue* InteractSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	class USoundCue* JumpSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	class USoundCue* ShootingSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	class USoundCue* MiningSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	class USoundCue* MiningCompletedSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	class USoundCue* IndoorFootStepsSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	class USoundCue* OutdoorFootstepsSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsOutdoor = true;

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

	UPROPERTY()
	AActor* HitActor = nullptr;
	UPROPERTY()
	class ACheckTerminalState* TerminalManager = nullptr;


	class IOutlineInterface* PreviouslyOutlinedActor = nullptr;
	UPROPERTY()
	class ABuildingInteractableBase* BuildingBase = nullptr;
	UPROPERTY()
	class AOreBase* Ore = nullptr;
	
	UPROPERTY()
	class UAudioComponent* CreatedMiningSound = nullptr;

	UPROPERTY()
	class UAudioComponent* CreatedShootingSound = nullptr;

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

	void StartMine();
	void Mine();
	void StopMine();

	UFUNCTION()
	void CallPauseMenu();
	UFUNCTION()
	void CallSettingsMenu();
	UFUNCTION()
	void ImStuckButton();

	void PushFinishScreen();


#pragma endregion Inputs

#pragma region Components

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Weapon;
	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* WeaponFire; 

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
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUpgradeWidgetBase> UpgradeWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UEndWidgetBase> EndWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UTutorialWidgetBase> TutorialWidget;
	
	
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
	UPROPERTY()
	class UUpgradeWidgetBase* CreatedUpgradeWidget = nullptr;
	UPROPERTY()
	class UEndWidgetBase* CreatedEndWidget = nullptr;
	UPROPERTY()
	class UTutorialWidgetBase* CreatedTutorialWidget = nullptr;

#pragma endregion UI

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY()
	AActor* TargetToFocus = nullptr;

	UPROPERTY()
	APlayerController* ActivePlayerController = nullptr;
	UPROPERTY()
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
	UFUNCTION()
	void ClearUpgradeWidget();
	UFUNCTION()
	void PushGameplayWidget();


};







