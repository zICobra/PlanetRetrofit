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

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* WidgetComponent;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(EditAnywhere, Category = "Building")
	int32 BuildingIndex;
	UPROPERTY(EditAnywhere, Category = "Building")
	bool IsFarm;

	DECLARE_DELEGATE(FOnInteract);
	DECLARE_DELEGATE(FOnEndOverlap);

	FOnInteract Interacting;
	FOnEndOverlap StoppedOverlapping;


	virtual void Interact() override;

};
