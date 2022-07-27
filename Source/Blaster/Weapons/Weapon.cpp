// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Blaster/Characters/BlasterCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"


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
	// PickupWidgetComponent configuration
	PickupWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupInfoWidget"));
	PickupWidgetComponent->SetupAttachment(RootComponent);
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, WeaponState);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	PickupWidgetComponent->SetVisibility(false);

	if (HasAuthority())
	{
		PickupAreaSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		PickupAreaSphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,
		                                                         ECollisionResponse::ECR_Overlap);
		PickupAreaSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::HandleOnComponentBeginOverlap);
		PickupAreaSphereComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::HandleOnComponentEndOverlap);
	}
}

void AWeapon::SetPickupWidgetComponentVisibility(const bool bValue) const
{
	PickupWidgetComponent->SetVisibility(bValue);
}

void AWeapon::OnRep_WeaponState()
{
	if(WeaponState == EWeaponState::EWS_Equipped)
	{
		SetPickupWidgetComponentVisibility(false);
	}
}

void AWeapon::HandleOnComponentBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
	if (!BlasterCharacter) return;
	BlasterCharacter->AddOverlappingWeaponToArray(this);
}

void AWeapon::HandleOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
	if (!BlasterCharacter) return;
	BlasterCharacter->RemoveOverlappingWeaponToArray(this);
}

void AWeapon::UpdateWeaponState(EWeaponState NextWeaponState)
{
	WeaponState = NextWeaponState;

	if(NextWeaponState == EWeaponState::EWS_Equipped)
	{
		SetPickupWidgetComponentVisibility(false);
		PickupAreaSphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}