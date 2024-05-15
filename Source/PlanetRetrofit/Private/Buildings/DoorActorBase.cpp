// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/DoorActorBase.h"

#include "Components/BoxComponent.h"
// Sets default values
ADoorActorBase::ADoorActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	DoorPosition = CreateDefaultSubobject<USceneComponent>(TEXT("DoorPosition"));
	DoorPosition->SetupAttachment(Root);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(Root);

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	LeftDoor->SetupAttachment(DoorPosition);
	
	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	RightDoor->SetupAttachment(DoorPosition);
}

// Called when the game starts or when spawned
void ADoorActorBase::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ADoorActorBase::OnBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ADoorActorBase::OnEndOverlap);
	
}

// Called every frame
void ADoorActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(IsBigDoor)
	{
		BigDoorOpeningCooldown -= DeltaTime * 1.5f;
		if(BigDoorOpeningCooldown <= 0)
		{
			if(Entered && DoorPosition->GetRelativeLocation() != EndPosition)
			{
				FVector CurrentLocation = DoorPosition->GetRelativeLocation();
				FVector NewLocation = FMath::Lerp(CurrentLocation, EndPosition, OpeningSpeed * DeltaTime);
				
				DoorPosition->SetRelativeLocation(NewLocation);
			}
			
		}
	}
	else
	{
		if(Entered && DoorPosition->GetRelativeLocation() != EndPosition)
		{
			FVector CurrentLocation = DoorPosition->GetRelativeLocation();
			FVector NewLocation = FMath::Lerp(CurrentLocation, EndPosition, OpeningSpeed * DeltaTime);
		

			DoorPosition->SetRelativeLocation(NewLocation);
		}
	}

	if(Exited  && DoorPosition->GetRelativeLocation() != StartPosition)
	{
		FVector CurrentLocation = DoorPosition->GetRelativeLocation();
		FVector NewLocation = FMath::Lerp(CurrentLocation, StartPosition, OpeningSpeed * DeltaTime);
	
		DoorPosition->SetRelativeLocation(NewLocation);
	}

}

void ADoorActorBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Exited = false;
	BigDoorOpeningCooldown = DoorCooldown;
	Entered = true;
}

void ADoorActorBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Entered = false;
	Exited = true;
}

