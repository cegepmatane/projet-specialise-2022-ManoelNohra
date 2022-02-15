// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    sprint = 1.0f;
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    FPSCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FisrtPersonCamera"));
    check(FPSCameraComp != nullptr);

    FPSCameraComp->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

    FPSCameraComp->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

    FPSCameraComp->bUsePawnControlRotation = true;

    FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
    check(FPSMesh != nullptr);

    FPSMesh->SetOnlyOwnerSee(true);

    FPSMesh->SetupAttachment(FPSCameraComp);

    FPSMesh->bCastDynamicShadow = false;
    FPSMesh->CastShadow = false;

    GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(GEngine != nullptr);

    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("HELOOOOOOOOOOOOOOOOOOOO!!!!!!!!!!!!"));

}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveX", this, &AFPSCharacter::MooveForward);
    PlayerInputComponent->BindAxis("MoveY", this, &AFPSCharacter::MooveRight);

    PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this,&AFPSCharacter::StopJump);

    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPSCharacter::StartSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFPSCharacter::StopSprint);

    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
    PlayerInputComponent->BindAction("Grappin", IE_Pressed, this, &AFPSCharacter::Grappin);
}

void AFPSCharacter::MooveForward(float value)
{
    FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    AddMovementInput(direction, value * sprint);
}
void AFPSCharacter::MooveRight(float value)
{
    FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(direction, value* sprint);
}

void AFPSCharacter::StartJump()
{
    bPressedJump = true;
}
void AFPSCharacter::StopJump()
{
    bPressedJump = false;
}
void AFPSCharacter::Fire()
{
    if (ProjectileClass)
    {
        FVector CamLocation;
        FRotator CamRotation;
        GetActorEyesViewPoint(CamLocation, CamRotation);

        MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

        FVector MuzzleLocation = CamLocation + FTransform(CamRotation).TransformVector(MuzzleOffset);

        FRotator MuzzleRotation = CamRotation;
        MuzzleRotation.Pitch += 10.0f;

        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
            if (Projectile)
            {
                FVector LunchDirection = MuzzleRotation.Vector();
                Projectile->FireInDirection(LunchDirection);
            }

        }
    }
}

void AFPSCharacter::StartSprint()
{
    sprint = 3.0f;
}
void AFPSCharacter::StopSprint()
{
    sprint = 1.0f;
}

void AFPSCharacter::Grappin()
{
    if (!isGrappling)
    {
        if (GrappinClass)
        {
            FVector CamLocation;
            FRotator CamRotation;
            GetActorEyesViewPoint(CamLocation, CamRotation);

            MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

            FVector MuzzleLocation = CamLocation + FTransform(CamRotation).TransformVector(MuzzleOffset);

            FRotator MuzzleRotation = CamRotation;
            FRotator Rotation = MuzzleRotation;
            Rotation.Pitch += 80.0f;
            Rotation.Yaw += 90.0f;
            UWorld* World = GetWorld();
            if (World)
            {
                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = this;
                SpawnParams.Instigator = GetInstigator();
                FVector GrappStart = MuzzleLocation;
                AGrappin* grappin = World->SpawnActor<AGrappin>(GrappinClass, MuzzleLocation, Rotation, SpawnParams);
                if (grappin)
                {
                    isGrappling = true;
                    while (!grappin->isCollision)
                    {
                        FVector LunchDirection = MuzzleRotation.Vector();
                        FVector scale = grappin->GetActorScale3D();
                        grappin->SetActorRelativeScale3D(scale+LunchDirection);

                    }
                    FVector GrappEnd = grappin->GetActorLocation();
                }

            }
        }

    }
    else
    {
        isGrappling = false;
    }
}