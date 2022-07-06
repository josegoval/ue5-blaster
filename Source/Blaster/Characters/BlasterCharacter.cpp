// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
}

// Called when the game starts or when spawned
void ABlasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

void ABlasterCharacter::Jump()
{
	Super::Jump();
}

