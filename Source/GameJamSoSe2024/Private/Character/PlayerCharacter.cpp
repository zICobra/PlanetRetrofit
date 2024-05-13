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
#include "UI/SettingsMenuBase.h"
#include "UI/PauseMenuBase.h"

#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"

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

	if(bSuccess && HitResult.GetActor() && HitResult.GetActor() != PreviouslyOutlinedActor)
	{
		
	}
	else if(!bSuccess && PreviouslyOutlinedActor)
	{

		PreviouslyOutlinedActor = nullptr;
	}

#pragma endregion Outline



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

	PEI->BindAction(InputActions->InputMine, ETriggerEvent::Started, this, &APlayerCharacter::Mine);

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
		CreatedGamePlayMenu->PullUpMaterialUI(StoneAmount, IronAmount, CopperAmount, AmethystAmount, PlatinAmount);
	}
}

void APlayerCharacter::Mine()
{
	
}

#pragma region UI

void APlayerCharacter::CallPauseMenu()
{
	if(!CreatedPauseMenu || !ActivePlayerController || !CreatedGameUIBase)
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
