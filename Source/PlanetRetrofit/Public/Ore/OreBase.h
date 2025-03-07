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
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* PlayerRadius;
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* BillboardRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore")
	class UNiagaraSystem* FishParticleSystem;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ore")
	int32 FishAmount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ore")
	float FishScale;


	UPROPERTY()
	AActor* Player = nullptr;
	UPROPERTY()
	class AOreManager* OreManager;

#pragma region OreType
public:

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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsStone", EditConditionHides))
	float StoneMiningDuration = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsIron", EditConditionHides))
	float IronMiningDuration = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsCopper", EditConditionHides))
	float CopperMiningDuration = 7.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsAmethyst", EditConditionHides))
	float AmethystMiningDuration = 9.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsPlatin", EditConditionHides))
	float PlatinMiningDuration = 12.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsStone", EditConditionHides))
	UStaticMesh* StoneStaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsIron", EditConditionHides))
	UStaticMesh* IronStaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsCopper", EditConditionHides))
	UStaticMesh* CopperStaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsAmethyst", EditConditionHides))
	UStaticMesh* AmethystStaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ore", meta = (EditCondition = "IsPlatin", EditConditionHides))
	UStaticMesh* PlatinStaticMesh;

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
	virtual bool CanOutline() override;

	virtual void StartMining(const FVector MinerPosition) override;
	virtual bool DoneMining() override;
	virtual FString OreType();

	void PlayMineAnimation();
	void RemoveMineAnimation();

	UPROPERTY(EditAnywhere, Category = "Mining", meta = (EditCondition = "IsStone", EditConditionHides))
	int32 StoneAmountPerOreMined = 1;
	UPROPERTY(EditAnywhere, Category = "Mining", meta = (EditCondition = "IsIron", EditConditionHides))
	int32 IronAmountPerOreMined = 1;
	UPROPERTY(EditAnywhere, Category = "Mining", meta = (EditCondition = "IsCopper", EditConditionHides))
	int32 CopperAmountPerOreMined = 1;
	UPROPERTY(EditAnywhere, Category = "Mining", meta = (EditCondition = "IsAmethyst", EditConditionHides))
	int32 AmethystAmountPerOreMined = 1;
	UPROPERTY(EditAnywhere, Category = "Mining", meta = (EditCondition = "IsPlatin", EditConditionHides))
	int32 PlatinAmountPerOreMined = 1;

private:
	void MiningScaleAndRotation();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void OnBillboardBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBillboardEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	void PlayFishNiagara();
	void RemoveFishNiagara();
	
	void FinishedMining();

	class UNiagaraComponent* CreatedFishParticleSystem = nullptr;
	class UNiagaraComponent* CreatedMiningParticleSystem = nullptr;

	float DestroyTime = 0.3f;

public:
	bool IsMined = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ore")
	bool SpawnFishParticle;

};
