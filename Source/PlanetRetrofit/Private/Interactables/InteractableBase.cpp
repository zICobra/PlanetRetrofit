// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/InteractableBase.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void AInteractableBase::Interact()
{
	
}

void AInteractableBase::OutlineTarget()
{
	Mesh->SetRenderCustomDepth(true);
}

void AInteractableBase::RemoveOutline()
{
	Mesh->SetRenderCustomDepth(false);
}

bool AInteractableBase::CanOutline()
{
	return true;
}

