// Fill out your copyright notice in the Description page of Project Settings.


#include "Perso.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Projectile.h"
#include "Hook.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PrototypeGameModeBase.h"




// Sets default values
APerso::APerso()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(40.f, 95.f);

	JumpCount = 0;
	Jumping = false;
	canShoot = false;
	canDoubleJump = false;
	canSprint = false;
	canHook = false;
	canSlide = false;
	walking = true;
	isSliding = false;
	isHooking = false;
	h = nullptr;

	speed = 0.7f;
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

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLocation->SetupAttachment(GunMesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffset = FVector(100.f, 0.0f, 10.0f);
}

// Called when the game starts or when spawned
void APerso::BeginPlay()
{
	Super::BeginPlay();
	GunMesh->AttachToComponent(HandsMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GripPoint"));
	World = GetWorld();
}

// Called every frame
void APerso::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Jumping)
	{
		Jump();
	}

	
}

// Called to bind functionality to input
void APerso::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APerso::CheckJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APerso::CheckJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APerso::OnFire);

	PlayerInputComponent->BindAxis("MoveForward", this, &APerso::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APerso::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APerso::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APerso::LookUpAtRate);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APerso::Sprint);

	PlayerInputComponent->BindAction("Hook", IE_Pressed, this, &APerso::Hook);
	
}


void APerso::OnFire()
{
	if (World != NULL)
	{
		SpawnRotation = GetControlRotation();

		SpawnLocation = ((MuzzleLocation != nullptr) ? 
			MuzzleLocation->GetComponentLocation() : 
			GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		World->SpawnActor<AProjectile>(Projectile, SpawnLocation, SpawnRotation, ActorSpawnParams);

		if(FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}
	}
}

void APerso::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	JumpCount = 0;
}

void APerso::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value * speed);
	}
	if (Value <= 0.0f)
	{
		walking = true;
		speed = 0.7f;
	}

}

void APerso::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value * speed);
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

void APerso::CheckJump()
{
	if (Jumping)
	{
		Jumping = false;
	}
	else
	{
		Jumping = true;
		JumpCount++;
		if (JumpCount == 2)
		{
			LaunchCharacter(FVector(0.f, 0.f, 750.f), false, true); 
		}
	}
}

void APerso::Sprint()
{
	walking = !walking;
	if (walking)
	{
		speed = 0.7f;
	}
	else
	{
		speed = 1.5f;
	}
}

void APerso::Hook()
{
	if (h != nullptr)
	{
		h->Destroy();
	}
	if (World != NULL && !isHooking)
	{
		SpawnRotation = GetControlRotation();

		SpawnLocation = ((MuzzleLocation != nullptr) ?
			MuzzleLocation->GetComponentLocation() :
			GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		h = World->SpawnActor<AHook>(hook, SpawnLocation, SpawnRotation, ActorSpawnParams);
		isHooking = true;
	}
	else
	{
		if (&h != NULL)
		{
			h->Destroy();
		}
		isHooking = false;
	}
}


void APerso::CanHook(bool change)
{
	canHook = change;
}

void APerso::CanSprint(bool change)
{
	canSprint = change;
}

void APerso::CanDoubleJump(bool change)
{
	canDoubleJump = change;
}

void APerso::CanShoot(bool change)
{
	canShoot = change;
}

void APerso::CanSlide(bool change)
{
	canSlide = change;
}
