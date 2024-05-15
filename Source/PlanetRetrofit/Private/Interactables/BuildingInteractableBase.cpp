// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/BuildingInteractableBase.h"

#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"


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

    TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABuildingInteractableBase::OnBeginOverlap);
    TriggerBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ABuildingInteractableBase::OnEndOverlap);
}

void ABuildingInteractableBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Interacting.ExecuteIfBound();
}

void ABuildingInteractableBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    StoppedOverlapping.ExecuteIfBound();
}

void ABuildingInteractableBase::Interact()
{
    // Interacting.ExecuteIfBound();
}
