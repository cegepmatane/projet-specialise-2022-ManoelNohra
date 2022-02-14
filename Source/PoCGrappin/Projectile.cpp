// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!colComp)
	{
		colComp = CreateAbstractDefaultSubobject<USphereComponent>(TEXT("SpehreComponent"));

		colComp->InitSphereRadius(15.0f);

		RootComponent = colComp;
	}

	if (!moveComp)
	{
		moveComp = CreateAbstractDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		moveComp->SetUpdatedComponent(colComp);
		moveComp->InitialSpeed = 3000.0f;
		moveComp->MaxSpeed = 3000.0f;
		moveComp->bRotationFollowsVelocity = true;
		moveComp->bShouldBounce = true;
		moveComp->Bounciness = 0.3f;
		moveComp->ProjectileGravityScale = 0.0f;
	}


	if (!projMeshComp)
	{
		projMeshComp = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Mesh/Sphere.Sphere'"));
		if (Mesh.Succeeded())
		{
			projMeshComp->SetStaticMesh(Mesh.Object);
		}
		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/Mesh/SphereMaterial.SphereMaterial'"));
		if (Material.Succeeded())
		{
			ProjMatInstance = UMaterialInstanceDynamic::Create(Material.Object, projMeshComp);
		}
		projMeshComp->SetMaterial(0, ProjMatInstance);
		projMeshComp->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
		projMeshComp->SetupAttachment(RootComponent);
	}

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection(const FVector& shootDirection)
{

}

