// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Pickable UMETA(DisplayName = "Pickable"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_Dropped UMETA(DisplayName = "Dropped"),

	EWS_MAX UMETA(DisplayName = "Default MAX"),
};

UCLASS()
class BLASTER_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();

	UFUNCTION()
	void SetPickupWidgetComponentVisibility(const bool bValue) const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	class USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	class USphereComponent* PickupAreaSphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	EWeaponState WeaponState;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	class UWidgetComponent* PickupWidgetComponent;


	UFUNCTION()
	void HandleOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                                   bool bFromSweep,
	                                   const FHitResult& SweepResult);
	UFUNCTION()
	void HandleOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
