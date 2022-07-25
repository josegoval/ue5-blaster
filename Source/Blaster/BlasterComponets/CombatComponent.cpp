// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "Blaster/Characters/BlasterCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Blaster/Weapons/Weapon.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::EquipWeapon(AWeapon* WeaponToEquip)
{
	if (!BlasterCharacter || !WeaponToEquip) return;

	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	EquippedWeapon->SetPickupWidgetComponentVisibility(false);
	USkeletalMeshComponent* MeshComponent = BlasterCharacter->GetMesh();
	const USkeletalMeshSocket* SkeletalMeshSocket = MeshComponent->GetSocketByName(
		BlasterCharacterSockets::RightHandSocket);
	if(!SkeletalMeshSocket) return;
	SkeletalMeshSocket->AttachActor(EquippedWeapon, MeshComponent);
}
