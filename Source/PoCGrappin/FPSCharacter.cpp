// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

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


}

void AFPSCharacter::MooveForward(float value)
{
    FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    AddMovementInput(direction, value);
}
void AFPSCharacter::MooveRight(float value)
{
    FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(direction, value);
}

void AFPSCharacter::StartJump()
{
    bPressedJump = true;
}
void AFPSCharacter::StopJump()
{
    bPressedJump = false;
}