// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BlasterCharacter.generated.h"

UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABlasterCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void MoveForward(float Value);
	UFUNCTION()
	void MoveRight(float Value);
	UFUNCTION()
	void LookUpMouse(float Value);
	UFUNCTION()
	void TurnRightMouse(float Value);
	UFUNCTION()
	void Equip();
	virtual void Jump() override;
	UFUNCTION()
	void HandleCrouch();

	UFUNCTION()
	void AddOverlappingWeaponToArray(class AWeapon* OverlappingWeapon);
	UFUNCTION()
	void RemoveOverlappingWeaponToArray(AWeapon* OverlappingWeapon);

	bool HasWeaponEquipped();

	
protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	TArray<AWeapon*> OverlappingWeaponsArray;

	UPROPERTY()
	class UCombatComponent* CombatComponent;

	UFUNCTION()
	void OnRep_OverlappingWeapon(TArray<AWeapon*> PrevValue);

	UFUNCTION(Server, Reliable)
	void ServerEquip();
};

namespace BlasterCharacterSockets
{
	inline FName RightHandSocket = FName(TEXT("RightHandSocket"));
}
