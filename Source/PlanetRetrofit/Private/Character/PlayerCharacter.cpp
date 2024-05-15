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
#include "UI/SettingsMenuBase.h"
#include "UI/DeathScreenBase.h"
#include "UI/PauseMenuBase.h"

#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"

#include "Interfaces/InteractableInterface.h"
#include "Interfaces/OutlineInterface.h"
#include "Interfaces/OreInterface.h"

#include "Interactables/BuildingInteractableBase.h"

#include "Sound/SoundCue.h"
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
	// DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 10, 0, 1);
	if(bSuccess)
	{
		if(IOutlineInterface* OutlineActor = Cast<IOutlineInterface>(HitResult.GetActor()))
		{
			if(OutlineActor != PreviouslyOutlinedActor)
			{
				OutlineActor->OutlineTarget();
				PreviouslyOutlinedActor = OutlineActor;
			}
			else if(OutlineActor == PreviouslyOutlinedActor)
			{

			}
			else
			{
				PreviouslyOutlinedActor->RemoveOutline();
				UE_LOG(LogTemp, Warning, TEXT("remove"));
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
		CurrentOxygen -= DeltaTime * 10;
		CreatedGamePlayMenu->SetOxygenBar(MaxOxygen, CurrentOxygen);
		if(CurrentOxygen <= 0)
		{
			CurrentHealth -= DeltaTime * 10.0f;
			CreatedGamePlayMenu->SetHealthBar(MaxHealth, CurrentHealth);
			if(CurrentHealth <= 0)
			{
				CreatedGameUIBase->PushDeathScreen(CreatedDeathScreen);
				ActivePlayerController->SetPause(true);
			}
		}
	}
	else
	{
		CurrentOxygen = FMath::Clamp(CurrentOxygen + DeltaTime * 2, 0, MaxOxygen);
		CurrentHealth = FMath::Clamp(CurrentHealth + DeltaTime * 2, 0, MaxHealth);
		CreatedGamePlayMenu->SetOxygenBar(MaxOxygen, CurrentOxygen);
		CreatedGamePlayMenu->SetHealthBar(MaxHealth, CurrentHealth);
	}

#pragma endregion Oxygen

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

	PEI->BindAction(InputActions->InputMine, ETriggerEvent::Triggered, this, &APlayerCharacter::Mine);

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
		if(BuildingBase = Cast<ABuildingInteractableBase>(HitResult.GetActor()))
		{
			BuildingBase->Interacting.BindUObject(this, &APlayerCharacter::ShowBuildingMenu);
			BuildingBase->StoppedOverlapping.BindUObject(this, &APlayerCharacter::ClearBuildingMenu);
			CreatedBuildingWidget->BuildingIndex = BuildingBase->BuildingIndex;
			CreatedBuildingWidget->IsFarm = BuildingBase->IsFarm;
		}
		if(IInteractableInterface* Interactable = Cast<IInteractableInterface>(HitResult.GetActor()))
		{
			Interactable->Interact();
		}
	}
}

void APlayerCharacter::PullUpMaterialUI()
{
	if(CreatedGamePlayMenu && CreatedGamePlayMenu->MaterialUIIsActive)
	{
		CreatedGamePlayMenu->RemoveMaterialUI();
	}
	else if(CreatedGamePlayMenu)
	{
		CreatedGamePlayMenu->PullUpMaterialUI(GameInstance->SaveGame->StoneAmount, GameInstance->SaveGame->IronAmount, GameInstance->SaveGame->CopperAmount, GameInstance->SaveGame->AmethystAmount, GameInstance->SaveGame->PlatinAmount);
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
		if(IOreInterface* Ore = Cast<IOreInterface>(HitResult.GetActor()))
		{	
			if(!Ore->DoneMining())
			{
				Ore->StartMining(GetActorLocation());
				if(Ore->DoneMining() && Ore->OreType() == "Stone")
				{
					GameInstance->SaveGame->StoneAmount += StoneAmountPerOreMined;
					UE_LOG(LogTemp, Warning, TEXT("%d"), GameInstance->SaveGame->StoneAmount);
				}
				else if(Ore->DoneMining() && Ore->OreType() == "Iron")
				{
					GameInstance->SaveGame->IronAmount += IronAmountPerOreMined;
				}
				else if(Ore->DoneMining() && Ore->OreType() == "Copper")
				{
					GameInstance->SaveGame->CopperAmount += CopperAmountPerOreMined;
				}
				else if(Ore->DoneMining() && Ore->OreType() == "Amethyst")
				{
					GameInstance->SaveGame->AmethystAmount += AmethystAmountPerOreMined;
				}
				else if(Ore->DoneMining() && Ore->OreType() == "Platin")
				{
					GameInstance->SaveGame->PlatinAmount += PlatinAmountPerOreMined;
				}
			}
		}
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
	CreatedBuildingWidget->OnBackButtonClicked.BindUObject(this, &APlayerCharacter::ClearBuildingMenu);
}

void APlayerCharacter::ClearBuildingMenu()
{
	CreatedGameUIBase->ClearBuildingMenu();
	
	CreatedBuildingWidget->OnBackButtonClicked.Unbind();
	BuildingBase->Interacting.Unbind();
	BuildingBase->StoppedOverlapping.Unbind();
}