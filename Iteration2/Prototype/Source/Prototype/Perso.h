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

	virtual void Landed(const FHitResult& Hit) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* HandsMesh;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* GunMesh;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* MuzzleLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* FirstPersonCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float TurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float LookUpRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
		int JumpCount;

protected:
	void OnFire();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void CheckJump();

	void Sprint();

	void CanHook(bool change);
	void CanSprint(bool change);
	void CanDoubleJump(bool change);
	void CanShoot(bool change);


public: 
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	class UAnimeInstance* AnimInstance;
	
	class UWorld* World;

	FRotator SpawnRotation;
	FVector SpawnLocation;

	bool Jumping;

	UPROPERTY()
		float speed;
	UPROPERTY()
		bool walking;
	UPROPERTY()
		bool canShoot;
	UPROPERTY()
		bool canSprint;
	UPROPERTY()
		bool canHook;
	UPROPERTY()
		bool canDoubleJump;
};
