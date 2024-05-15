// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/InteractableInterface.h"
#include "Interfaces/OutlineInterface.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

UCLASS()
class PLANETRETROFIT_API AInteractableBase : public AActor, public IInteractableInterface, public IOutlineInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

public:	

	virtual void Interact() override;

	virtual void OutlineTarget() override;
	virtual void RemoveOutline() override;
	virtual bool CanOutline() override;


};
