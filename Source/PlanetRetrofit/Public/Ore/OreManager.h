// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OreManager.generated.h"

UCLASS()
class PLANETRETROFIT_API AOreManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOreManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY()
	class UDefaultGameInstance* GameInstance = nullptr;

	UFUNCTION()
	void IsLoadedGame();
	void LoadOreState();
	void NewOreState();

public: 
	void MinedOre(class AOreBase* Ore);
	
};
