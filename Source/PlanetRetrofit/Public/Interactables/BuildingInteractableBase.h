// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/InteractableBase.h"
#include "BuildingInteractableBase.generated.h"

/**
 * 
 */
UCLASS()
class PLANETRETROFIT_API ABuildingInteractableBase : public AInteractableBase
{
	GENERATED_BODY()

protected:
	ABuildingInteractableBase();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building")
	class USoundCue* BuildingSound;


	UPROPERTY()
	class UDefaultGameInstance* GameInstance = nullptr;

public:
	UPROPERTY(EditAnywhere, Category = "Building")
	int32 BuildingIndex;
	UPROPERTY(EditAnywhere, Category = "Building")
	FTransform BuildingTransform;
	UPROPERTY(EditAnywhere, Category = "Building")
	bool IsFarm;

	UPROPERTY()
	bool Spawned = false;
	UPROPERTY()
	int32 SpawnedFarmIndex = 0;

	DECLARE_DELEGATE(FOnInteract);

	FOnInteract Interacting;


	virtual void Interact() override;
	virtual bool CanOutline() override;

	void BuildBuilding();


};
