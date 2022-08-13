// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


class ABlasterCharacter;
class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()
	friend class ABlasterCharacter;
public:	
	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void EquipWeapon(AWeapon* WeaponToEquip);
	
protected:
	virtual void BeginPlay() override;
	void SetIsAiming(bool Value);

	UFUNCTION(Server, Reliable)
	void ServerSetIsAiming(bool Value);

private:
	UPROPERTY()
	ABlasterCharacter* BlasterCharacter;
	UPROPERTY(Replicated, VisibleAnywhere)
	AWeapon* EquippedWeapon;
	
	UPROPERTY(Replicated)
	bool bIsAiming;
		
};
