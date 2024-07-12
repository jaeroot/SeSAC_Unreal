// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SESAC_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

};
