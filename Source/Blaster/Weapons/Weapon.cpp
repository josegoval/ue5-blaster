// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/SphereComponent.h"


// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	bReplicates = true;

	// SkeletalMeshComponent configuration
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SetRootComponent(SkeletalMeshComponent);
	SkeletalMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SkeletalMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// PickupAreaSphereComponent configuration
	PickupAreaSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("PickupAreaSphere"));
	PickupAreaSphereComponent->SetupAttachment(RootComponent);
	PickupAreaSphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PickupAreaSphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		PickupAreaSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		PickupAreaSphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,
		                                                         ECollisionResponse::ECR_Overlap);
	}
}
