// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/BedBase.h"

#include "DefaultGameInstance.h"


void ABedBase::BeginPlay()
{
    GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());
}


void ABedBase::Interact()
{
    if(GameInstance)
    {
        GameInstance->SaveGameState();
    }
}

