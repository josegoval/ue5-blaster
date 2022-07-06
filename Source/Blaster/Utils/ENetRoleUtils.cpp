// Fill out your copyright notice in the Description page of Project Settings.


#include "ENetRoleUtils.h"



FString ENetRoleUtils::GetENetRoleString(const ENetRole& Role)
{
	switch (Role)
	{
	case ENetRole::ROLE_Authority:
		return FString(TEXT("Authority"));
	case ENetRole::ROLE_AutonomousProxy:
		return FString(TEXT("Autonomous proxy"));
	case ENetRole::ROLE_SimulatedProxy:
		return FString(TEXT("Simulated proxy"));
	case ENetRole::ROLE_None:
		return FString(TEXT("None"));
	default:
		return FString(TEXT("Unknown"));
	}
}
