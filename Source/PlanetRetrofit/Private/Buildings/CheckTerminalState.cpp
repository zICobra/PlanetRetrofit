// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/CheckTerminalState.h"

#include "DefaultGameInstance.h"
#include "SaveGame/DefaultSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

#include "Interactables/BuildingInteractableBase.h"

// Sets default values
ACheckTerminalState::ACheckTerminalState()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACheckTerminalState::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());

	GameInstance->TerminalLoadedSettingsDelegate.BindUObject(this, &ACheckTerminalState::IsLoadedGame);
	
}

void ACheckTerminalState::IsLoadedGame()
{
	if(GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("FoundTerminal"));
		if(GameInstance->LoadGame)
		{
			if(GameInstance->SaveGame)
			{
				LoadTerminalState();
			}
		}
		else if(GameInstance->SaveGame)
		{
			GameInstance->SaveGame->TerminalSaveDataArray.Empty();
			NewGameTerminalState();
		}
	}
}

void ACheckTerminalState::LoadTerminalState()
{	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuildingInteractableBase::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
    	ABuildingInteractableBase* Terminal = Cast<ABuildingInteractableBase>(Actor); 
		
		for (const FTerminalSaveData& TerminalData : GameInstance->SaveGame->TerminalSaveDataArray)
        {
            if (Terminal->GetActorLocation() == TerminalData.Location)
            {
                Terminal->Spawned = TerminalData.HasSpawned;
				Terminal->BuildingIndex = TerminalData.BuildingIndex;
				UE_LOG(LogTemp, Warning, TEXT("%d"), Terminal->BuildingIndex);
				Terminal->OnLoadGameCheck();
                break;
            }
        }
    }
}

void ACheckTerminalState::NewGameTerminalState()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuildingInteractableBase::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
    	ABuildingInteractableBase* Terminal = Cast<ABuildingInteractableBase>(Actor); 

        FTerminalSaveData NewTerminalData;

        NewTerminalData.HasSpawned = Terminal->Spawned;
		NewTerminalData.BuildingIndex = Terminal->BuildingIndex;
        NewTerminalData.Location = Terminal->GetActorLocation();
        
        GameInstance->SaveGame->TerminalSaveDataArray.Add(NewTerminalData);
    }
}

void ACheckTerminalState::SpawnedBuilding(class ABuildingInteractableBase* Terminal)
{
	for (FTerminalSaveData& TerminalData : GameInstance->SaveGame->TerminalSaveDataArray)
	{
		if (Terminal->GetActorLocation() == TerminalData.Location)
		{
			TerminalData.HasSpawned = Terminal->Spawned;
			TerminalData.BuildingIndex = Terminal->BuildingIndex;
			break;
		}
	}
}

bool ACheckTerminalState::AllBuildingsBuild()
{
	for (const FTerminalSaveData& TerminalData : GameInstance->SaveGame->TerminalSaveDataArray)
	{
		if (!TerminalData.HasSpawned)
		{
			UE_LOG(LogTemp, Warning, TEXT("false"));
			return false;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("true"));
	return true;
}


