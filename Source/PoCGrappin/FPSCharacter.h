// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Projectile.h"
#include "Grappin.h"
#include "FPSCharacter.generated.h"

UCLASS()
class POCGRAPPIN_API AFPSCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AFPSCharacter();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = Projectile)
        TSubclassOf<class AProjectile> ProjectileClass;
    UPROPERTY(EditDefaultsOnly, Category = Grappin)
        TSubclassOf<class AGrappin> GrappinClass;

    UPROPERTY(EditAnywhere)
        float sprint;
    UPROPERTY(EditAnywhere)
        float isGrappling;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


    UFUNCTION()
        void MooveForward(float value);
    UFUNCTION()
        void MooveRight(float value);
    UFUNCTION()
        void StartJump();
    UFUNCTION()
        void StopJump();
    UFUNCTION()
        void StartSprint();
    UFUNCTION()
        void StopSprint();
    UFUNCTION()
        void Fire();
    UFUNCTION()
        void Grappin();

    UPROPERTY(EditAnywhere, Category = Camera)
        UCameraComponent* FPSCameraComp;

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
        USkeletalMeshComponent* FPSMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
        FVector MuzzleOffset;


};

