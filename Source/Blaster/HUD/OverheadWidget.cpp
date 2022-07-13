// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"

#include "Blaster/Utils/ENetRoleUtils.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverheadWidget::DisplayENetRoles(APawn* Pawn) const
{
	if(!Pawn) return;

	const ENetRole LocalRole = Pawn->GetLocalRole();
	const ENetRole RemoteRole = Pawn->GetRemoteRole();

	const FString DisplayText = FString::Printf(
		TEXT("Local Role: %s\nRemote Role: %s"),
		*ENetRoleUtils::GetENetRoleString(LocalRole),
		*ENetRoleUtils::GetENetRoleString(RemoteRole)
	);
	OverheadText->SetText(FText::FromString(DisplayText));
}

void UOverheadWidget::DisplayPlayerName(APawn* Pawn) const
{
	if(!Pawn) return;
	const APlayerState* PlayerState = Pawn->GetPlayerState();
	if(!PlayerState)return;
	OverheadText->SetText(FText::FromString(PlayerState->GetPlayerName()));
}

void UOverheadWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
	RemoveFromParent();
}
