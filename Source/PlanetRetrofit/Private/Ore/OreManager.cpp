// Fill out your copyright notice in the Description page of Project Settings.


#include "Ore/OreManager.h"

#include "DefaultGameInstance.h"
#include "SaveGame/DefaultSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

#include "Ore/OreBase.h"

// Sets default values
AOreManager::AOreManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AOreManager::BeginPlay()
{
	Super::BeginPlay();
	
	GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());

	GameInstance->OreLoadedSettingsDelegate.BindUObject(this, &AOreManager::IsLoadedGame);

}

void AOreManager::IsLoadedGame()
{
	if(GameInstance)
	{
		if(GameInstance->LoadGame)
		{
			if(GameInstance->SaveGame)
			{
				LoadOreState();
			}
		}
		else if(GameInstance->SaveGame)
		{
			GameInstance->SaveGame->OreSaveDataArray.Empty();
			NewOreState();
		}
	}
}

void AOreManager::LoadOreState()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOreBase::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
        AOreBase* Ore = Cast<AOreBase>(Actor);
        if (Ore)
        {	
            for (const FOreSaveData& OreData : GameInstance->SaveGame->OreSaveDataArray)
            {
                if (Ore->GetActorLocation() == OreData.Location)
                {
					UE_LOG(LogTemp, Warning, TEXT("Location"));
                    if (OreData.IsMined)
                    {
						UE_LOG(LogTemp, Warning, TEXT("Destroy"));
                        Ore->Destroy();
                        break;
                    }
                }
            }
        }
    }
}

void AOreManager::NewOreState()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOreBase::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
        AOreBase* Ore = Cast<AOreBase>(Actor);

		if(Ore)
		{
			FOreSaveData NewOreData;

			NewOreData.IsMined = Ore->IsMined;
			NewOreData.Location = Ore->GetActorLocation();
			
			GameInstance->SaveGame->OreSaveDataArray.Add(NewOreData);
		}
    }
}

void AOreManager::MinedOre(class AOreBase* Ore)
{
	for (FOreSaveData& OreData : GameInstance->SaveGame->OreSaveDataArray)
	{
		if (Ore->GetActorLocation() == OreData.Location)
		{
			OreData.IsMined = Ore->IsMined;
			break;
		}
	}
}


