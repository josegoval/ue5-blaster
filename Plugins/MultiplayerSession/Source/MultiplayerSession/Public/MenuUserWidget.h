// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSION_API UMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Setup(const int32 MaxPlayers = 4,
	           const FString MatchType = FString(TEXT("FreeForAll")),
	           const FString PathToLobbyMap = FString(TEXT("/Game/ThirdPerson/Maps/Lobby")));

protected:
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSession(const TArray<FOnlineSessionSearchResult>& SearchResults,
	                   bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);

private:
	// Widget vars
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY()
	class UMultiplayerSessionGISubsystem* MultiplayerSessionGISubsystem;

	// Session configuration
	int32 SavedMaxPlayers = 4;
	FString SavedMatchType = FString(TEXT("FreeForAll"));
	FString SavedPathToLobbyMap = FString(TEXT(""));

	UFUNCTION()
	void HandleClickHostButton();
	UFUNCTION()
	void HandleClickJoinButton();

	void ActivateMenu();
	void DeactivateMenu();
	void EnableUIControls();
	void DisableUIControls();
	void ConfigureMultiplayerSessionGISubsystem();
	void ConfigureWidgetButtonBindings();
};
