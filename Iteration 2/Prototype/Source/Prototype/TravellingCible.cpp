// Fill out your copyright notice in the Description page of Project Settings.


#include "TravellingCible.h"

// Sets default values
ATravellingCible::ATravellingCible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Parent = GetOwner();
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ATravellingCible::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

// Called every frame
void ATravellingCible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WaitTime > 0)
	{
		WaitTime -= DeltaTime;
		return;
	}
	if (TimeElapsed < LerpDuration)
	{
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
		
	}
}

