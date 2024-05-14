// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/InteractableBase.h"
#include "BedBase.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API ABedBase : public AInteractableBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;


public:

	virtual void Interact() override;

private:

	UPROPERTY()
	class UDefaultGameInstance* GameInstance = nullptr;
	
};
