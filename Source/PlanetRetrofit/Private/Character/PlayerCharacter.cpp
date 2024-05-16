// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "DataAssets/InputConfig.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "SaveGame/DefaultSaveGame.h"
#include "DefaultGameInstance.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "UI/CommonUserWidgetBase.h"
#include "UI/GamePlayWidgetBase.h"
#include "UI/BuildingWidgetBase.h"
#include "UI/UpgradeWidgetBase.h"
#include "UI/SettingsMenuBase.h"
#include "UI/DeathScreenBase.h"
#include "UI/PauseMenuBase.h"

#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"

#include "Interfaces/InteractableInterface.h"
#include "Interfaces/OutlineInterface.h"

#include "Interactables/BuildingInteractableBase.h"
#include "Interactables/UpgradeStationBase.h"
#include "Ore/OreBase.h"

#include "LandscapeProxy.h"

#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "NiagaraSystem.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	ActivePlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());
		if(GameInstance)
		{
			GameInstance->LoadSettingsInMainLevel();
		}
	}

	if(ActivePlayerController)
	{
		ActivePlayerController->SetShowMouseCursor(false);
		ActivePlayerController->SetInputMode(GameOnlyInputMode);
	}

	CameraAnimation();
	CreatedMiningSound = NewObject<UAudioComponent>(this);
	if(CreatedMiningSound)
	{
		CreatedMiningSound->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		CreatedMiningSound->SetSound(MiningSound);
	}

	OxygenTag = GetGameplayTagsManager().RequestGameplayTag(FName("HasOxygen"));

#pragma region UI

	if(GameUIBase)
	{
		CreatedGameUIBase = Cast<UCommonUserWidgetBase>(CreateWidget<UCommonUserWidgetBase>(GetWorld(), GameUIBase));
		CreatedGameUIBase->AddToViewport(0);
	}

	if(PauseMenu)
	{
		CreatedPauseMenu = Cast<UPauseMenuBase>(CreateWidget<UCommonActivatableWidgetBase>(GetWorld(), PauseMenu));
	}
	if(SettingsMenu)
	{
		CreatedSettingsMenu = Cast<USettingsMenuBase>(CreateWidget<UCommonActivatableWidgetBase>(GetWorld(), SettingsMenu));
	}
	if(GamePlayUI)
	{
		CreatedGamePlayMenu = Cast<UGamePlayWidgetBase>(CreateWidget<UCommonActivatableWidgetBase>(GetWorld(), GamePlayUI));
	}
	if(DeathScreen)
	{
		CreatedDeathScreen = Cast<UDeathScreenBase>(CreateWidget<UCommonActivatableWidgetBase>(GetWorld(), DeathScreen));
	}
	if(BuildingWidget)
	{
		CreatedBuildingWidget = Cast<UBuildingWidgetBase>(CreateWidget<UCommonActivatableWidgetBase>(GetWorld(), BuildingWidget));
	}
	if(UpgradeWidget)
	{
		CreatedUpgradeWidget = Cast<UUpgradeWidgetBase>(CreateWidget<UCommonActivatableWidgetBase>(GetWorld(), UpgradeWidget));
	}


	CreatedGameUIBase->PushGamePlayMenu(CreatedGamePlayMenu);
	
#pragma endregion UI


}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#pragma region Outline

	static FVector StartPoint = FVector::Zero();
	static FVector EndPoint = FVector::Zero();
	static FRotator PlayerRotation = FRotator::ZeroRotator;

	Controller->GetPlayerViewPoint(StartPoint, PlayerRotation);

	EndPoint = StartPoint + PlayerRotation.Vector() * InteractionRange;

	FHitResult HitResult;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, Params);
	
	if(bSuccess)
	{
		if(IOutlineInterface* OutlineActor = Cast<IOutlineInterface>(HitResult.GetActor()))
		{
			if(OutlineActor != PreviouslyOutlinedActor && OutlineActor->CanOutline())
			{
				OutlineActor->OutlineTarget();
				PreviouslyOutlinedActor = OutlineActor;
			}
			else if(OutlineActor == PreviouslyOutlinedActor)
			{

			}
			else if(PreviouslyOutlinedActor)
			{
				PreviouslyOutlinedActor->RemoveOutline();
				PreviouslyOutlinedActor = nullptr;
			}
		}
		else if(PreviouslyOutlinedActor)
		{
			PreviouslyOutlinedActor->RemoveOutline();
			PreviouslyOutlinedActor = nullptr;
		}

	}
	else if(PreviouslyOutlinedActor)
	{
		PreviouslyOutlinedActor->RemoveOutline();
		PreviouslyOutlinedActor = nullptr;
	}

#pragma endregion Outline

#pragma region Oxygen

	if(!GameplayTags.HasTag(OxygenTag))
	{
		CurrentOxygen -= DeltaTime * GameInstance->SaveGame->OxygenDepletionMultiplier;
		UE_LOG(LogTemp, Warning, TEXT("OxygenMutilpier: %f"), GameInstance->SaveGame->OxygenDepletionMultiplier);
		CreatedGamePlayMenu->SetOxygenBar(MaxOxygen, CurrentOxygen);
		if(CurrentOxygen <= 0)
		{
			CurrentHealth -= DeltaTime * 7.0f;
			CreatedGamePlayMenu->SetHealthBar(MaxHealth, CurrentHealth);
			if(CurrentHealth <= 0)
			{
				CreatedGameUIBase->PushDeathScreen(CreatedDeathScreen);
				UGameplayStatics::PlaySound2D(GetWorld(), DeathSound);
				ActivePlayerController->SetPause(true);
			}
		}
	}
	else
	{
		CurrentOxygen = FMath::Clamp(CurrentOxygen + DeltaTime * 5, 0, MaxOxygen);
		CurrentHealth = FMath::Clamp(CurrentHealth + DeltaTime * 5, 0, MaxHealth);
		CreatedGamePlayMenu->SetOxygenBar(MaxOxygen, CurrentOxygen);
		CreatedGamePlayMenu->SetHealthBar(MaxHealth, CurrentHealth);
	}

#pragma endregion Oxygen


#pragma region Footsteps

	static FVector StartPointFootsteps = FVector::Zero();
	static FVector EndPointFootsteps = FVector::Zero();

	StartPointFootsteps = GetActorLocation();

	EndPointFootsteps = FVector(StartPointFootsteps.X, StartPointFootsteps.Y, StartPointFootsteps.Z - 150);

	FHitResult HitResultFootsteps;


	bool bSuccessFootsteps = GetWorld()->LineTraceSingleByChannel(HitResultFootsteps, StartPointFootsteps, EndPointFootsteps, ECC_Visibility, Params);
	
	if(bSuccessFootsteps)
	{
		if(Cast<ALandscapeProxy>(HitResultFootsteps.GetActor()))
		{
			IsOutdoor = true;
		}
		else
		{
			IsOutdoor = false;
		}
	}


#pragma endregion Footsteps



}



#pragma region Inputs

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(ActivePlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	PEI->BindAction(InputActions->InputControllerLook, ETriggerEvent::Triggered, this, &APlayerCharacter::LookController);

	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Started, this, &APlayerCharacter::StartJump);
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Canceled, this, &APlayerCharacter::StopJump);

	PEI->BindAction(InputActions->InputSprint, ETriggerEvent::Started, this, &APlayerCharacter::StartSprint);
	PEI->BindAction(InputActions->InputSprint, ETriggerEvent::Completed, this, &APlayerCharacter::StopSprint);

	PEI->BindAction(InputActions->InputControllerSprint, ETriggerEvent::Started, this, &APlayerCharacter::ControllerSprint);

	PEI->BindAction(InputActions->InputPullUpMaterialUI, ETriggerEvent::Started, this, &APlayerCharacter::PullUpMaterialUI);

	PEI->BindAction(InputActions->InputMine, ETriggerEvent::Started, this, &APlayerCharacter::StartMine);
	PEI->BindAction(InputActions->InputMine, ETriggerEvent::Triggered, this, &APlayerCharacter::Mine);
	PEI->BindAction(InputActions->InputMine, ETriggerEvent::Completed, this, &APlayerCharacter::StopMine);

	PEI->BindAction(InputActions->InputInteract, ETriggerEvent::Started, this, &APlayerCharacter::Interact);
	PEI->BindAction(InputActions->InputPauseMenu, ETriggerEvent::Started, this, &APlayerCharacter::CallPauseMenu);
}

#pragma region Movement

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	
	if(Controller)
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);
	
		//Forward/Backward direction
		if(MoveValue.Y != 0)
		{
			//Get forward vector
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(Direction, MoveValue.Y);
		}

		//Right/Left direction 
		if(MoveValue.X != 0)
		{
			//Get right vector
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

			AddMovementInput(Direction, MoveValue.X);
		}
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	if(Controller)
	{
		const FVector2D LookValue = Value.Get<FVector2D>();
		
		if(LookValue.X != 0)
		{
			AddControllerYawInput(LookValue.X * GameInstance->SaveGame->MouseSensitivity);
		}

		if(LookValue.Y != 0)
		{
			AddControllerPitchInput(-LookValue.Y * GameInstance->SaveGame->MouseSensitivity);
		}

		// UE_LOG(LogTemp, Warning, TEXT("MouseSens: %f"), GameInstance->SaveGame->MouseSensitivity);
	}
}

void APlayerCharacter::LookController(const FInputActionValue& Value)
{
	if(Controller)
	{
		const FVector2D LookValue = Value.Get<FVector2D>();
		
		if(LookValue.X != 0)
		{
			AddControllerYawInput(LookValue.X * GameInstance->SaveGame->ControllerSensitivity);
		}

		if(LookValue.Y != 0)
		{
			AddControllerPitchInput(LookValue.Y * GameInstance->SaveGame->ControllerSensitivity);
		}
	}
}

void APlayerCharacter::StartJump()
{
	Jump();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), JumpSound, GetActorLocation());
}

void APlayerCharacter::StopJump()
{
	StopJumping();
}

void APlayerCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APlayerCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::ControllerSprint()
{
	if(GetCharacterMovement()->MaxWalkSpeed = SprintSpeed)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

#pragma endregion Movement

void APlayerCharacter::Interact()
{
	static FVector StartPoint = FVector::Zero();
	static FVector EndPoint = FVector::Zero();
	static FRotator PlayerRotation = FRotator::ZeroRotator;

	Controller->GetPlayerViewPoint(StartPoint, PlayerRotation);

	EndPoint = StartPoint + PlayerRotation.Vector() * InteractionRange;

	FHitResult HitResult;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, Params);

	if(bSuccess && HitResult.GetActor())
	{
		BuildingBase = Cast<ABuildingInteractableBase>(HitResult.GetActor());
		if(BuildingBase && !BuildingBase->Spawned)
		{
			BuildingBase->Interacting.BindUObject(this, &APlayerCharacter::ShowBuildingMenu);
			CreatedBuildingWidget->BuildingIndex = BuildingBase->BuildingIndex;
			CreatedBuildingWidget->IsFarm = BuildingBase->IsFarm;
			if(BuildingBase->IsFarm)
			{
				CreatedBuildingWidget->IsFarm1 = BuildingBase->IsFarm1;
				CreatedBuildingWidget->IsFarm2 = BuildingBase->IsFarm2;
				CreatedBuildingWidget->IsFarm3 = BuildingBase->IsFarm3;
				CreatedBuildingWidget->IsFarm4 = BuildingBase->IsFarm4;
			}
		}
		if(IInteractableInterface* Interactable = Cast<IInteractableInterface>(HitResult.GetActor()))
		{
			Interactable->Interact();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractSound, GetActorLocation());
		}

		if(AUpgradeStationBase* UpgradeStation = Cast<AUpgradeStationBase>(HitResult.GetActor()))
		{
			UpgradeStation->Interact();
			CreatedGameUIBase->PushUpgradeWidget(CreatedUpgradeWidget);
			ActivePlayerController->SetShowMouseCursor(true);
			ActivePlayerController->SetInputMode(GameAndUIInputMode);
			CreatedUpgradeWidget->OnUpgradeUIBackButtonClicked.BindUObject(this, &APlayerCharacter::ClearUpgradeWidget);
		}
	}
}

void APlayerCharacter::PullUpMaterialUI()
{
	if(CreatedGamePlayMenu && CreatedGamePlayMenu->MaterialUIIsActive)
	{
		CreatedGamePlayMenu->RemoveMaterialUI();
		ActivePlayerController->SetShowMouseCursor(false);
		ActivePlayerController->SetInputMode(GameOnlyInputMode);
	}
	else if(CreatedGamePlayMenu)
	{
		CreatedGamePlayMenu->PullUpMaterialUI(GameInstance->SaveGame->StoneAmount, GameInstance->SaveGame->IronAmount, GameInstance->SaveGame->CopperAmount, GameInstance->SaveGame->AmethystAmount, GameInstance->SaveGame->PlatinAmount);
	}
}

void APlayerCharacter::StartMine()
{
	static FVector StartPoint = FVector::Zero();
	static FVector EndPoint = FVector::Zero();
	static FRotator PlayerRotation = FRotator::ZeroRotator;

	Controller->GetPlayerViewPoint(StartPoint, PlayerRotation);

	EndPoint = StartPoint + PlayerRotation.Vector() * InteractionRange;

	FHitResult HitResult;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, Params);

	if(bSuccess && HitResult.GetActor())
	{
		Ore = Cast<AOreBase>(HitResult.GetActor());
		if(Ore)
		{
			Ore->PlayMineAnimation();
			CreatedMiningSound->Play();
		}
	}
}

void APlayerCharacter::Mine()
{
	static FVector StartPoint = FVector::Zero();
	static FVector EndPoint = FVector::Zero();
	static FRotator PlayerRotation = FRotator::ZeroRotator;

	Controller->GetPlayerViewPoint(StartPoint, PlayerRotation);

	EndPoint = StartPoint + PlayerRotation.Vector() * InteractionRange;

	FHitResult HitResult;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, Params);

	if(bSuccess && HitResult.GetActor())
	{
		if(AOreBase* FocusedOre = Cast<AOreBase>(HitResult.GetActor()))
		{	
			if(!FocusedOre->DoneMining())
			{
				if(CreatedMiningSound->IsPlaying())
				{

				}
				else
				{
					CreatedMiningSound->Play();
				}

				FocusedOre->StartMining(GetActorLocation());
				if(FocusedOre->DoneMining() && FocusedOre->OreType() == "Stone")
				{
					GameInstance->SaveGame->StoneAmount += FocusedOre->StoneAmountPerOreMined;
					UE_LOG(LogTemp, Warning, TEXT("%d"), GameInstance->SaveGame->StoneAmount);
				}
				else if(FocusedOre->DoneMining() && FocusedOre->OreType() == "Iron")
				{
					GameInstance->SaveGame->IronAmount += FocusedOre->IronAmountPerOreMined;
				}
				else if(FocusedOre->DoneMining() && FocusedOre->OreType() == "Copper")
				{
					GameInstance->SaveGame->CopperAmount += FocusedOre->CopperAmountPerOreMined;
				}
				else if(FocusedOre->DoneMining() && FocusedOre->OreType() == "Amethyst")
				{
					GameInstance->SaveGame->AmethystAmount += FocusedOre->AmethystAmountPerOreMined;
				}
				else if(FocusedOre->DoneMining() && FocusedOre->OreType() == "Platin")
				{
					GameInstance->SaveGame->PlatinAmount += FocusedOre->PlatinAmountPerOreMined;
				}
			}
			else if(Ore)
			{
				Ore->RemoveMineAnimation();
				Ore = nullptr;
				
				CreatedMiningSound->Stop();
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), MiningCompletedSound, GetActorLocation());

				if(CreatedGamePlayMenu->MaterialUIIsActive)
				{
					CreatedGamePlayMenu->PullUpMaterialUI(GameInstance->SaveGame->StoneAmount, GameInstance->SaveGame->IronAmount, GameInstance->SaveGame->CopperAmount, GameInstance->SaveGame->AmethystAmount, GameInstance->SaveGame->PlatinAmount);
				}				
			}
		}
		else
		{
			CreatedMiningSound->Stop();
			if(Ore)
			{
				UE_LOG(LogTemp, Warning, TEXT("Remove"));
				Ore->RemoveMineAnimation();
				Ore = nullptr;
			}
		}
	}
	else
	{
		CreatedMiningSound->Stop();
		if(Ore)
		{
			UE_LOG(LogTemp, Warning, TEXT("Remove"));
			Ore->RemoveMineAnimation();
			Ore = nullptr;
		}
	}
	
}

void APlayerCharacter::StopMine()
{
	if(Ore)
	{
		Ore->RemoveMineAnimation();
		Ore = nullptr;
		CreatedMiningSound->Stop();
	}
}

#pragma region UI

void APlayerCharacter::CallPauseMenu()
{
	if(!CreatedPauseMenu || !ActivePlayerController || !CreatedGameUIBase || CreatedGameUIBase->DeathScreenActive || CreatedGameUIBase->BuildingMenuActive)
	{
		return;
	}

	if (ActivePlayerController->IsPaused())
	{
		CreatedPauseMenu->ResumButtonClickedDelagate.RemoveDynamic(this, &APlayerCharacter::CallPauseMenu);
		CreatedPauseMenu->SettingsButtonClickedDelegate.RemoveDynamic(this, &APlayerCharacter::CallSettingsMenu);
		CreatedGameUIBase->ClearPauseMenu();
		ActivePlayerController->SetShowMouseCursor(false);
		ActivePlayerController->SetInputMode(GameOnlyInputMode);
		ActivePlayerController->SetPause(false); 
	}
	else
	{
		CreatedGameUIBase->PushPauseMenu(CreatedPauseMenu);

		if(CreatedGameUIBase->PauseMenuActive)
		{
			ActivePlayerController->SetShowMouseCursor(true);
			ActivePlayerController->SetInputMode(GameAndUIInputMode);
			ActivePlayerController->SetPause(true);
			CreatedPauseMenu->ResumButtonClickedDelagate.AddUniqueDynamic(this, &APlayerCharacter::CallPauseMenu);
			CreatedPauseMenu->SettingsButtonClickedDelegate.AddUniqueDynamic(this, &APlayerCharacter::CallSettingsMenu);
		}
	}
	
}

void APlayerCharacter::CallSettingsMenu()
{
	CreatedGameUIBase->PushSettingsMenu(CreatedSettingsMenu);
}

#pragma endregion UI

UGameplayTagsManager& APlayerCharacter::GetGameplayTagsManager()
{
	static UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
	return GameplayTagsManager;
}

void APlayerCharacter::AddGameplayTag()
{
	GameplayTags.AddTag(OxygenTag);
}

void APlayerCharacter::RemoveGameplayTag()
{
	GameplayTags.RemoveTag(OxygenTag);
}

void APlayerCharacter::ShowBuildingMenu()
{
	CreatedGameUIBase->PushBuildingMenu(CreatedBuildingWidget);
	
	ActivePlayerController->SetShowMouseCursor(true);
	ActivePlayerController->SetInputMode(GameAndUIInputMode);

	CreatedBuildingWidget->OnBuildButtonClicked.BindUObject(this, &APlayerCharacter::SpawnBuilding);
	CreatedBuildingWidget->OnBackButtonClicked.BindUObject(this, &APlayerCharacter::ClearBuildingMenu);
}

void APlayerCharacter::ClearBuildingMenu()
{
	CreatedGameUIBase->ClearBuildingMenu();
	ActivePlayerController->SetInputMode(GameOnlyInputMode);
	ActivePlayerController->SetShowMouseCursor(false);

	CreatedBuildingWidget->OnBackButtonClicked.Unbind();
	BuildingBase->Interacting.Unbind();
}

void APlayerCharacter::SpawnBuilding(int32 BuildingIndex)
{
	ClearBuildingMenu();

	if(BuildingBase->IsFarm)
	{
		BuildingBase->BuildingIndex = BuildingIndex;
	}
	if(PreviouslyOutlinedActor)
	{
		PreviouslyOutlinedActor->RemoveOutline();
		PreviouslyOutlinedActor = nullptr;
	}

	BuildingBase->BuildBuilding();
}

void APlayerCharacter::ClearUpgradeWidget()
{
	CreatedGameUIBase->ClearUpgradeWidet();

	ActivePlayerController->SetInputMode(GameOnlyInputMode);
	ActivePlayerController->SetShowMouseCursor(false);

	CreatedUpgradeWidget->OnUpgradeUIBackButtonClicked.Unbind();
}