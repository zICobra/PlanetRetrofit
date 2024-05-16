// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActorBase.generated.h"

UCLASS()
class PLANETRETROFIT_API ADoorActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DoorPosition;
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LeftDoor;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RightDoor;

	UPROPERTY(EditAnywhere, Category = "Door")
	FVector StartPosition;
	UPROPERTY(EditAnywhere, Category = "Door")
	FVector EndPosition;

	UPROPERTY(EditAnywhere, Category = "Door")
	bool IsBigDoor = false;
	UPROPERTY(EditAnywhere, Category = "Door")
	float BigDoorOpeningCooldown = 2.0f;
	UPROPERTY(EditAnywhere, Category = "Door")
	float OpeningSpeed = 2.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door")
	class USoundCue* BuildingSound;

	bool Entered = false;
	bool Exited = false;
	float DoorCooldown = BigDoorOpeningCooldown;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
