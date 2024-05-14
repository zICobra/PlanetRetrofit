// Fill out your copyright notice in the Description page of Project Settings.


#include "Ore/OreBase.h"

#include "Components/BillboardComponent.h"
#include "NiagaraSystem.h"
#include "Sound/SoundCue.h"


// Sets default values
AOreBase::AOreBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	OreTypeText = CreateDefaultSubobject<UBillboardComponent>(TEXT("OreTypeText"));
	OreTypeText->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AOreBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOreBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOreBase::OutlineTarget()
{
	Mesh->SetRenderCustomDepth(true);
}

void AOreBase::RemoveOutline()
{
	Mesh->SetRenderCustomDepth(false);
}

void AOreBase::StartMining()
{
	
}

