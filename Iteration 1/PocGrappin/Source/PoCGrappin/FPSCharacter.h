// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Projectile.h"
#include "Hook.h"
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
    UPROPERTY(EditDefaultsOnly, Category = "Hook")
        TSubclassOf<class AHook> HookClass;

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
        void Fire();
    UFUNCTION()
        void Hook();

    UPROPERTY(VisibleAnywhere)
        UCameraComponent* FPSCameraComp;

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
        USkeletalMeshComponent* FPSMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
        FVector MuzzleOffset;

    UPROPERTY(EditAnywhere, Category = Gameplay)
        FVector HookStartLoc;
    UPROPERTY(EditAnywhere, Category = Gameplay)
        FVector HookEndLoc;

    UPROPERTY(VisibleAnywhere)
        bool isHooking;


};

