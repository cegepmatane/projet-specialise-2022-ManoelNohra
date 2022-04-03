// Fill out your copyright notice in the Description page of Project Settings.


#include "TravelCible.h"

// Sets default values for this component's properties
UTravelCible::UTravelCible()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Parent = GetOwner();
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	StartLocation = GetComponentLocation();
	stop = false;
}


// Called when the game starts
void UTravelCible::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTravelCible::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (WaitTime > 0)
	{
		WaitTime -= DeltaTime;
		return;
	}
	if (TimeElapsed < LerpDuration)
	{
		if (!stop)
		{
			TargetLocation += StartLocation;

		}
		Parent->SetActorLocation(FMath::Lerp(StartLocation, TargetLocation, TimeElapsed / LerpDuration));
		TimeElapsed += DeltaTime;
	}
	else
	{

		TimeElapsed = 0;
		FVector temp = StartLocation;
		TargetLocation = StartLocation;
		StartLocation = temp;
		WaitTime = 1;
		stop = true;
	}
}

