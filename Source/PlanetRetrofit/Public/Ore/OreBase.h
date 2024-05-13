// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OutlineInterface.h"
#include "Interfaces/OreInterface.h"
#include "GameFramework/Actor.h"
#include "OreBase.generated.h"

UCLASS()
class PLANETRETROFIT_API AOreBase : public AActor, public IOutlineInterface, public IOreInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOreBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	class UBillboardComponent* OreTypeText;

#pragma region OreType

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "!IsIron && !IsCopper && !IsAmethyst && !IsPlatin", EditConditionHides))
	bool IsStone;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "!IsStone && !IsCopper && !IsAmethyst && !IsPlatin", EditConditionHides))
	bool IsIron;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "!IsStone && !IsIron && !IsAmethyst && !IsPlatin", EditConditionHides))
	bool IsCopper;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "!IsStone && !IsIron && !IsCopper && !IsPlatin", EditConditionHides))
	bool IsAmethyst;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "!IsStone && !IsIron && !IsCopper && !IsAmethyst", EditConditionHides))
	bool IsPlatin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsStone", EditConditionHides))
	float StoneMiningDuration = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsIron", EditConditionHides))
	float IronMiningDuration = 1.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsCopper", EditConditionHides))
	float CopperMiningDuration = 2.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsAmethyst", EditConditionHides))
	float AmethystMiningDuration = 2.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsPlatin", EditConditionHides))
	float PlatinMiningDuration = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsStone", EditConditionHides))
	class UNiagaraSystem* StoneMiningParticleSystem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsIron", EditConditionHides))
	class UNiagaraSystem* IronMiningParticleSystem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsCopper", EditConditionHides))
	class UNiagaraSystem* CopperMiningParticleSystem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsAmethyst", EditConditionHides))
	class UNiagaraSystem* AmethystMiningParticleSystem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsPlatin", EditConditionHides))
	class UNiagaraSystem* PlatinMiningParticleSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsStone", EditConditionHides))
	class USoundCue* StoneMiningSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsIron", EditConditionHides))
	class USoundCue* IronMiningSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsCopper", EditConditionHides))
	class USoundCue* CopperMiningSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsAmethyst", EditConditionHides))
	class USoundCue* AmethystMiningSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsPlatin", EditConditionHides))
	class USoundCue* PlatinMiningSound;


#pragma endregion OreType



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OutlineTarget() override;
	virtual void RemoveOutline() override;

	virtual void StartMining() override;

};
