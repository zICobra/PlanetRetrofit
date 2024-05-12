// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GamePlayWidgetBase.h"

#include "DefaultGameInstance.h"
#include "Components/Overlay.h"
#include "CommonLazyImage.h"
#include "CommonTextBlock.h"
#include "Materials/MaterialInstance.h"
#include "Kismet/KismetMaterialLibrary.h"

void UGamePlayWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());

}

