// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "Blaster/Characters/BlasterCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Blaster/Weapons/Weapon.h"
#include "Net/UnrealNetwork.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatComponent::SetIsAiming(const bool Value)
{
	bIsAiming = Value;
	ServerSetIsAiming(Value);
}

void UCombatComponent::ServerSetIsAiming_Implementation(const bool Value)
{
	bIsAiming = Value;
}


void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCombatComponent, EquippedWeapon);
	DOREPLIFETIME(UCombatComponent, bIsAiming);
}

void UCombatComponent::EquipWeapon(AWeapon* WeaponToEquip)
{
	if (!BlasterCharacter || !WeaponToEquip) return;

	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->UpdateWeaponState(EWeaponState::EWS_Equipped);
	USkeletalMeshComponent* MeshComponent = BlasterCharacter->GetMesh();
	const USkeletalMeshSocket* SkeletalMeshSocket = MeshComponent->GetSocketByName(
		BlasterCharacterSockets::RightHandSocket);
	if(!SkeletalMeshSocket) return;
	SkeletalMeshSocket->AttachActor(EquippedWeapon, MeshComponent);
}

