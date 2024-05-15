// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/BuildingInteractableBase.h"

#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"


#include "DefaultGameInstance.h"

#include "DataAssets/BuildingsConfig.h"


ABuildingInteractableBase::ABuildingInteractableBase()
{
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
    TriggerBox->SetupAttachment(Root);

    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
    WidgetComponent->SetupAttachment(Root);
}

void ABuildingInteractableBase::BeginPlay()
{
    Super::BeginPlay();

    GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());

    TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABuildingInteractableBase::OnBeginOverlap);
    TriggerBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ABuildingInteractableBase::OnEndOverlap);
}

void ABuildingInteractableBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ABuildingInteractableBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    StoppedOverlapping.ExecuteIfBound();
}

void ABuildingInteractableBase::Interact()
{
    if(Spawned)
    {
        return;
    }
    Interacting.ExecuteIfBound();
}

void ABuildingInteractableBase::BuildBuilding()
{
    FActorSpawnParameters SpawnParams;

    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // Set collision handling

    if(!GameInstance->BuildingConfig->Buildings[BuildingIndex].ActorToSpawn)
    {
        UE_LOG(LogTemp, Error, TEXT("Actor to Spawn for %s is Empty!!!"), *GameInstance->BuildingConfig->Buildings[BuildingIndex].BuildingName);
        return;
    }

    GetWorld()->SpawnActor(GameInstance->BuildingConfig->Buildings[BuildingIndex].ActorToSpawn, &BuildingTransform, SpawnParams);
    Spawned = true;
}

bool ABuildingInteractableBase::CanOutline()
{
    if(Spawned)
    {
        return false;
    }
    else
    {
        return true;
    }
}
