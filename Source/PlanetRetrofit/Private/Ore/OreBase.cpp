// Fill out your copyright notice in the Description page of Project Settings.


#include "Ore/OreBase.h"

#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

#include "Interfaces/GamplayTagsInterface.h" 

#include "Ore/OreManager.h"


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

	PlayerRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Player Radius"));
	PlayerRadius->SetupAttachment(Root);

	BillboardRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Billboard Radius"));
	BillboardRadius->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AOreBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerRadius->OnComponentBeginOverlap.AddUniqueDynamic(this, &AOreBase::OnBeginOverlap);
	PlayerRadius->OnComponentEndOverlap.AddUniqueDynamic(this, &AOreBase::OnEndOverlap);

	BillboardRadius->OnComponentBeginOverlap.AddUniqueDynamic(this, &AOreBase::OnBillboardBeginOverlap);
	BillboardRadius->OnComponentEndOverlap.AddUniqueDynamic(this, &AOreBase::OnBillboardEndOverlap);

	if(SpawnFishParticle)
	{
		PlayFishNiagara();
	}

	OreManager = Cast<AOreManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AOreManager::StaticClass()));
}

// Called every frame
void AOreBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Player)
	{
		if(CreatedFishParticleSystem)
		{
			CreatedFishParticleSystem->SetVectorParameter(TEXT("PlayerPosition"), Player->GetActorLocation());
		}

		if(CreatedMiningParticleSystem)
		{
			// CreatedMiningParticleSystem->SetVectorParameter(TEXT("EndLocation"), FVector(0, 0, 0));
			FVector RelativeLocation = Player->GetActorLocation() - GetActorLocation();
			CreatedMiningParticleSystem->SetVectorParameter(TEXT("EndLocation"), RelativeLocation);
		}
	}

	if(IsMined)
	{
		DestroyTime -= DeltaTime;
		if(DestroyTime <= 0)
		{
			PlayerRadius->OnComponentBeginOverlap.RemoveDynamic(this, &AOreBase::OnBeginOverlap);
			PlayerRadius->OnComponentEndOverlap.RemoveDynamic(this, &AOreBase::OnEndOverlap);

			BillboardRadius->OnComponentBeginOverlap.RemoveDynamic(this, &AOreBase::OnBillboardBeginOverlap);
			BillboardRadius->OnComponentEndOverlap.RemoveDynamic(this, &AOreBase::OnBillboardEndOverlap);

			RemoveFishNiagara();
			FinishedMining();
			OreManager->MinedOre(this);
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

bool AOreBase::CanOutline()
{
	return true;
}

void AOreBase::StartMining(const FVector MinerPosition)
{
	if(CreatedMiningParticleSystem && CreatedMiningParticleSystem->IsActive())
	{

	}
	else if(CreatedMiningParticleSystem)
	{
		CreatedMiningParticleSystem->Activate();
	}


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
	if(Mesh->GetRelativeScale3D().X >= 0.2f && Mesh->GetRelativeScale3D().Y >= 0.2f && Mesh->GetRelativeScale3D().Z >= 0.2f)
	{
		if(IsStone || IsIron)
		{
			Mesh->SetWorldScale3D(FVector(Mesh->GetComponentScale().X - 0.009f, Mesh->GetComponentScale().Y - 0.009f, Mesh->GetComponentScale().Z - 0.009f));
		}
		else
		{
			Mesh->SetWorldScale3D(FVector(Mesh->GetComponentScale().X - 0.002f, Mesh->GetComponentScale().Y - 0.002f, Mesh->GetComponentScale().Z - 0.002f));
		}
	}

}

void AOreBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IGamplayTagsInterface* Interface = Cast<IGamplayTagsInterface>(OtherActor))
	{
		Player = OtherActor;
	}
}

void AOreBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(Cast<IGamplayTagsInterface>(OtherActor))
	{		
		Player = nullptr;
	}
}

void AOreBase::OnBillboardBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IGamplayTagsInterface* Interface = Cast<IGamplayTagsInterface>(OtherActor))
	{
		OreTypeText->SetHiddenInGame(false);
	}
}

void AOreBase::OnBillboardEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(IGamplayTagsInterface* Interface = Cast<IGamplayTagsInterface>(OtherActor))
	{
		OreTypeText->SetHiddenInGame(true);
	}
}

void AOreBase::PlayFishNiagara()
{
	CreatedFishParticleSystem = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FishParticleSystem, GetActorLocation());

	CreatedFishParticleSystem->SetVariableInt(TEXT("FishAmount"), FishAmount);
	CreatedFishParticleSystem->SetVariableFloat(TEXT("FishScale"), FishScale);
	
	if(IsStone)
	{
		CreatedFishParticleSystem->SetVariableLinearColor(TEXT("FishColor"), FLinearColor::Red);
	}
	else if(IsIron)
	{
		CreatedFishParticleSystem->SetVariableLinearColor(TEXT("FishColor"), FLinearColor::Gray);
	}
	else if(IsCopper)
	{
		CreatedFishParticleSystem->SetVariableLinearColor(TEXT("FishColor"), FLinearColor::Green);
	}
	else if(IsAmethyst)
	{
		CreatedFishParticleSystem->SetVariableLinearColor(TEXT("FishColor"), FLinearColor::Blue);
	}
	else if(IsPlatin)
	{
		CreatedFishParticleSystem->SetVariableLinearColor(TEXT("FishColor"), FLinearColor::Yellow);
	}
}

void AOreBase::RemoveFishNiagara()
{
	if(CreatedFishParticleSystem)
	{
		CreatedFishParticleSystem->SetVariableBool(TEXT("OreMined"), true);

    	float Lifespan = 2.0f; // Lifespan in seconds

    	FTimerHandle TimerHandle;
    	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() 
		{
        	CreatedFishParticleSystem->DestroyComponent();
			CreatedFishParticleSystem = nullptr;
    	}, Lifespan, false);

	}
}

void AOreBase::PlayMineAnimation()
{
	if(CreatedMiningParticleSystem && CreatedMiningParticleSystem->IsActive())
	{
		return;
	}

	if(IsStone)
	{
		CreatedMiningParticleSystem = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), StoneMiningParticleSystem, GetActorLocation());
		CreatedMiningParticleSystem->Activate();
		CreatedMiningParticleSystem->SetVariableStaticMesh(TEXT("Ore"), StoneStaticMesh);
	}
	else if(IsIron)
	{
		CreatedMiningParticleSystem = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), IronMiningParticleSystem, GetActorLocation());
		CreatedMiningParticleSystem->Activate();
		CreatedMiningParticleSystem->SetVariableStaticMesh(TEXT("Ore"), IronStaticMesh);
	}
	else if(IsCopper)
	{
		CreatedMiningParticleSystem = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), CopperMiningParticleSystem, GetActorLocation());
		CreatedMiningParticleSystem->Activate();
		CreatedMiningParticleSystem->SetVariableStaticMesh(TEXT("Ore"), CopperStaticMesh);
	}
	else if(IsAmethyst)
	{
		CreatedMiningParticleSystem = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), AmethystMiningParticleSystem, GetActorLocation());
		CreatedMiningParticleSystem->Activate();
		CreatedMiningParticleSystem->SetVariableStaticMesh(TEXT("Ore"), AmethystStaticMesh);
	}
	else if(IsPlatin)
	{
		CreatedMiningParticleSystem = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), PlatinMiningParticleSystem, GetActorLocation());
		CreatedMiningParticleSystem->Activate();
		CreatedMiningParticleSystem->SetVariableStaticMesh(TEXT("Ore"), PlatinStaticMesh);
	}
}

void AOreBase::RemoveMineAnimation()
{
	if(CreatedMiningParticleSystem)
	{
		FTimerHandle TimerHandle;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() 
		{
			if(CreatedMiningParticleSystem)
			{
				CreatedMiningParticleSystem->Deactivate();
				CreatedMiningParticleSystem = nullptr;
			}
		}, 1.0f, false);
	}
}

void AOreBase::FinishedMining()
{
	if(CreatedMiningParticleSystem)
	{
		CreatedMiningParticleSystem->DestroyComponent();
		CreatedMiningParticleSystem = nullptr;
	}
}
