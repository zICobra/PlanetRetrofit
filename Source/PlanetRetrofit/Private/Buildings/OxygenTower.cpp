// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/OxygenTower.h"

#include "Components/SphereComponent.h"
#include "Interfaces/GamplayTagsInterface.h"


AOxygenTower::AOxygenTower()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(Root);
    OxygenRange = CreateDefaultSubobject<USphereComponent>(TEXT("Oxygen Range"));
    OxygenRange->SetupAttachment(Root);
}

void AOxygenTower::BeginPlay()
{
    Super::BeginPlay();

    OxygenRange->OnComponentBeginOverlap.AddUniqueDynamic(this, &AOxygenTower::OnBeginOverlap);
    OxygenRange->OnComponentEndOverlap.AddUniqueDynamic(this, &AOxygenTower::OnEndOverlap);

}

void AOxygenTower::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(OtherActor)
    {
        if(IGamplayTagsInterface* TagsInterface = Cast<IGamplayTagsInterface>(OtherActor))
        {
            TagsInterface->AddGameplayTag();
        }
    }
    
}

void AOxygenTower::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if(OtherActor)
    {
        if(IGamplayTagsInterface* TagsInterface = Cast<IGamplayTagsInterface>(OtherActor))
        {
            TagsInterface->RemoveGameplayTag();
        }
    } 
}

