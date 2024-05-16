// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/InteractableBase.h"
#include "UpgradeStationBase.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API AUpgradeStationBase : public AInteractableBase
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	class UDefaultGameInstance* GameInstance = nullptr;


public:

	virtual void Interact() override;
	virtual bool CanOutline() override;
	
};
