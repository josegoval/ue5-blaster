// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterCharacter.h"

#include "Blaster/BlasterComponets/CombatComponent.h"
#include "Blaster/Weapons/Weapon.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABlasterCharacter::ABlasterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Spring arm setup
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("SpringArm")));
	SpringArmComponent->SetupAttachment(GetMesh());
	SpringArmComponent->TargetArmLength = 600;
	SpringArmComponent->bUsePawnControlRotation = true;
	// Follow camera setup
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("FollowCamera")));
	FollowCamera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	// Set control setup
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Widget setup
	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(RootComponent);
	// Combat component setup
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	CombatComponent->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void ABlasterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABlasterCharacter::OnRep_OverlappingWeapon(TArray<AWeapon*> PrevValue)
{
	// If it's not in the previous array then set it as visible 
	for (AWeapon* OverlappingWeapon : OverlappingWeaponsArray)
	{
		if (PrevValue.Contains(OverlappingWeapon)) continue;
		OverlappingWeapon->SetPickupWidgetComponentVisibility(true);
	}
	// If it's not in the current array then set is as not visible
	for (AWeapon* OverlappingWeapon : PrevValue)
	{
		if (OverlappingWeaponsArray.Contains(OverlappingWeapon)) continue;
		OverlappingWeapon->SetPickupWidgetComponentVisibility(false);
	}
}

void ABlasterCharacter::ServerEquip_Implementation()
{
	if(!OverlappingWeaponsArray.Num()) return;
	CombatComponent->EquipWeapon(OverlappingWeaponsArray[0]);
}

// Called every frame
void ABlasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind axis
	PlayerInputComponent->BindAxis(FName(TEXT("Move Forward / Backward")), this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis(FName(TEXT("Move Right / Left")), this, &ThisClass::MoveRight);
	PlayerInputComponent->BindAxis(FName(TEXT("Look Up / Down Mouse")), this, &ThisClass::LookUpMouse);
	PlayerInputComponent->BindAxis(FName(TEXT("Turn Right / Left Mouse")), this, &ThisClass::TurnRightMouse);
	// Bind actions	
	PlayerInputComponent->BindAction(FName(TEXT("Jump")), EInputEvent::IE_Pressed, this, &ThisClass::Jump);
	PlayerInputComponent->BindAction(FName(TEXT("Equip")), EInputEvent::IE_Pressed, this, &ThisClass::Equip);
}

void ABlasterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ABlasterCharacter, OverlappingWeaponsArray, COND_OwnerOnly);
}

void ABlasterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(!CombatComponent) return;
	CombatComponent->BlasterCharacter = this;
}

void ABlasterCharacter::MoveForward(float Value)
{
	AddMovementInput(FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X), Value);
}


void ABlasterCharacter::MoveRight(float Value)
{
	AddMovementInput(FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y), Value);
}

void ABlasterCharacter::LookUpMouse(float Value)
{
	AddControllerPitchInput(Value);
}

void ABlasterCharacter::TurnRightMouse(float Value)
{
	AddControllerYawInput(Value);
}

void ABlasterCharacter::Equip()
{
	if(!HasAuthority())	return ServerEquip();
	ServerEquip_Implementation();
}

void ABlasterCharacter::Jump()
{
	Super::Jump();
}

void ABlasterCharacter::AddOverlappingWeaponToArray(AWeapon* OverlappingWeapon)
{
	OverlappingWeaponsArray.AddUnique(OverlappingWeapon);
	if (IsLocallyControlled())
	{
		OverlappingWeapon->SetPickupWidgetComponentVisibility(true);
	}
}

void ABlasterCharacter::RemoveOverlappingWeaponToArray(AWeapon* OverlappingWeapon)
{
	OverlappingWeaponsArray.Remove(OverlappingWeapon);
	if (IsLocallyControlled())
	{
		OverlappingWeapon->SetPickupWidgetComponentVisibility(false);
	}
}
