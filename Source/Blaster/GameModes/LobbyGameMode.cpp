// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState.Get()->PlayerArray.Num() >= PlayersRequiredToStartMatch)
	{
		UWorld* World = GetWorld();
		if (!World) return;
		bUseSeamlessTravel = true;
		World->ServerTravel(FString(TEXT("/Game/Maps/BlasterMap")));
	}
}
