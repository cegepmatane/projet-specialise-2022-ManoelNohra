// Fill out your copyright notice in the Description page of Project Settings.


#include "Hook.h"
#include "Components/SphereComponent.h"
#include "Perso.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AHook::AHook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Spehere Collision"));
	CollisionSphere->InitSphereRadius(20.0f);

	RootComponent = CollisionSphere;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->UpdatedComponent = CollisionSphere;
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	InitialLifeSpan = 5.0f;
}

// Called when the game starts or when spawned
void AHook::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHook::OnHit);
}

// Called every frame
void AHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHook::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{

}