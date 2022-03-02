// Fill out your copyright notice in the Description page of Project Settings.


#include "Perso.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"


// Sets default values
APerso::APerso()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(40.f, 95.f);

	TurnRate = 45.f;
	LookUpRate = 45.f;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FisrtPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->AddRelativeLocation(FVector(-35.65f, 1.75f, 64.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));

	HandsMesh->SetOnlyOwnerSee(true);
	HandsMesh->SetupAttachment(FirstPersonCamera);
	HandsMesh->bCastDynamicShadow = false;
	HandsMesh->AddRelativeRotation(FRotator(1.9f, -19.9f, 5.2f));
	HandsMesh->AddRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetOnlyOwnerSee(true);

	MuzzleLocation = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLocation->SetupAttachment(GunMesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffset = FVector(100.f, 0.0f, 10.0f);
}

// Called when the game starts or when spawned
void APerso::BeginPlay()
{
	Super::BeginPlay();
	GunMesh->AttachToComponent(HandsMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GripPoint"));
}

// Called every frame
void APerso::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APerso::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APerso::OnFire);

	PlayerInputComponent->BindAxis("MoveForward", this, &APerso::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APerso::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APerso::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APerso::LookUpAtRate);

}

void APerso::OnFire()
{
}

void APerso::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APerso::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APerso::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate*TurnRate*GetWorld()->GetDeltaSeconds());
}

void APerso::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * LookUpRate * GetWorld()->GetDeltaSeconds());
}

