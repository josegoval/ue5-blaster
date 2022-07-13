// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API UOverheadWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* OverheadText;

	UFUNCTION(BlueprintCallable)
	void DisplayENetRoles(APawn* Pawn) const;
	UFUNCTION(BlueprintCallable)
	void DisplayPlayerName(APawn* Pawn) const;
protected:
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
};
