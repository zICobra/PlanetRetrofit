// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckTerminalState.generated.h"

UCLASS()
class PLANETRETROFIT_API ACheckTerminalState : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckTerminalState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	class UDefaultGameInstance* GameInstance = nullptr;

	UFUNCTION()
	void IsLoadedGame();
	void LoadTerminalState();
	void NewGameTerminalState();
	

public:
	void SpawnedBuilding(class ABuildingInteractableBase* Terminal); 

	bool AllBuildingsBuild();


};
