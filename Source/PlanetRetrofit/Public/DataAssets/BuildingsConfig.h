// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/StaticMeshActor.h"

#include "BuildingsConfig.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FBuildingData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString BuildingName = "";
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 StoneAmount = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 IronAmount = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 CopperAmount = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AmethystAmount = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 PlatinAmount = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AStaticMeshActor> ActorToSpawn;

};


UCLASS()
class PLANETRETROFIT_API UBuildingsConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FBuildingData> Buildings;
};
