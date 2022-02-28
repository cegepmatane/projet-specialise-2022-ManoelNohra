// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perso.generated.h"

UCLASS()
class PROTOTYPE_API APerso : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APerso();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PersoMesh;
	UPROPERTY(EditAnywhere)
		class UCameraComponent* PersoCam;
	UPROPERTY(EditAnywhere)


};
