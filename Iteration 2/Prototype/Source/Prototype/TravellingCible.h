// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TravellingCible.generated.h"

UCLASS()
class PROTOTYPE_API ATravellingCible : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATravellingCible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float TimeElapsed = 0;
	AActor* Parent = nullptr;
	FVector StartLocation;

	UPROPERTY(VisibleDefaultsOnly, Category = Lerp)
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = Lerp, Meta = (MakeEditWidget = true))
		FVector TargetLocation;
	UPROPERTY(EditAnywhere, Category = Lerp)
		float LerpDuration = 3;
	UPROPERTY(EditAnywhere, Category = Lerp)
		float WaitTime = 3;

};
