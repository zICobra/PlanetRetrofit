// Fill out your copyright notice in the Description page of Project Settings.


#include "Ore/OreBase.h"

#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
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

	FishRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Fish Radius"));
	FishRadius->SetupAttachment(Root);
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

	if(IsMined)
	{
		DestroyTime -= DeltaTime;
		if(DestroyTime <= 0)
		{
			Destroy();
		}
	}
}

void AOreBase::OutlineTarget()
{
	Mesh->SetRenderCustomDepth(true);
}

void AOreBase::RemoveOutline()
{
	Mesh->SetRenderCustomDepth(false);
}

void AOreBase::StartMining(const FVector MinerPosition)
{
	if(IsStone)
	{
		StoneMiningDuration -= GetWorld()->GetDeltaSeconds() * 3.5f;
		if(StoneMiningDuration <= 0)
		{
			IsMined = true;
		}
		else
		{
			MiningScaleAndRotation();
		}
	}
	else if(IsIron)
	{
		IronMiningDuration -= GetWorld()->GetDeltaSeconds() * 3.5f;
		if(IronMiningDuration <= 0)
		{
			IsMined = true;
		}
		else
		{
			MiningScaleAndRotation();
		}
	}
	else if(IsCopper)
	{
		CopperMiningDuration -= GetWorld()->GetDeltaSeconds() * 3.5f;
		if(CopperMiningDuration <= 0)
		{
			IsMined = true;
		}
		else
		{
			MiningScaleAndRotation();
		}
	}
	else if(IsAmethyst)
	{
		AmethystMiningDuration -= GetWorld()->GetDeltaSeconds() * 3.5f;
		if(AmethystMiningDuration <= 0)
		{
			IsMined = true;
		}
		else
		{
			MiningScaleAndRotation();
		}
	}
	else if(IsPlatin)
	{
		PlatinMiningDuration -= GetWorld()->GetDeltaSeconds() * 3.5f;
		if(PlatinMiningDuration <= 0)
		{
			IsMined = true;
		}
		else
		{
			MiningScaleAndRotation();
		}
	}
}

bool AOreBase::DoneMining()
{
	return IsMined;
}

FString AOreBase::OreType()
{
	if(IsStone)
	{
		return "Stone";
	}
	else if(IsIron)
	{
		return "Iron";
	}
	else if(IsCopper)
	{
		return "Copper";
	}
	else if(IsAmethyst)
	{
		return "Amethyst";
	}
	else 
	{
		return "Platin";
	}
}

void AOreBase::MiningScaleAndRotation()
{
	if(IsStone || IsIron)
	{
		Mesh->SetWorldScale3D(FVector(Mesh->GetComponentScale().X - 0.01f, Mesh->GetComponentScale().Y - 0.01f, Mesh->GetComponentScale().Z - 0.01f));
	}
	else
	{
		Mesh->SetWorldScale3D(FVector(Mesh->GetComponentScale().X - 0.001f, Mesh->GetComponentScale().Y - 0.001f, Mesh->GetComponentScale().Z - 0.001f));
	}

	Mesh->SetWorldRotation(FRotator(Mesh->GetComponentRotation().Pitch, Mesh->GetComponentRotation().Yaw + 5, Mesh->GetComponentRotation().Roll));
}

