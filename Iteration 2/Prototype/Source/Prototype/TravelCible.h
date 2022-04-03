// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TravelCible.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPE_API UTravelCible : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTravelCible();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private : 
	float TimeElapsed = 0;
	AActor* Parent = nullptr;
	FVector StartLocation;
	bool stop;

	UPROPERTY(VisibleDefaultsOnly, Category = Lerp)
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = Lerp, Meta = (MakeEditWidget = true))
		FVector TargetLocation;
	UPROPERTY(EditAnywhere, Category = Lerp)
		float LerpDuration = 5;
	UPROPERTY(EditAnywhere, Category = Lerp)
		float WaitTime = 3;
		
};
