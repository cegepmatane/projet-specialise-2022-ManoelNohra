// Fill out your copyright notice in the Description page of Project Settings.


#include "Hook.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
// Sets default values
AHook::AHook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	hookMesh = CreateDefaultSubobject<UStaticMeshComponent>("HookMesh");

	hookMov = CreateDefaultSubobject<UProjectileMovementComponent>("HookMovementComponent");
	Col = CreateDefaultSubobject<UBoxComponent>("Box");
	Col->OnComponentHit.AddDynamic(this, &AHook::OnHit);
	InitialLifeSpan = 1.0f;
}

// Called when the game starts or when spawned
void AHook::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHook::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

}