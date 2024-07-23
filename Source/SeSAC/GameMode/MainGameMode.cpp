// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "../Player/KnightCharacter.h"
#include "SeSAC/SeSACGameInstance.h"
#include "SeSAC/AI/Monster/MonsterDataManager.h"
#include "SeSAC/Player/InGamePlayerController.h"
#include "SeSAC/Player/SeSACPlayerState.h"

AMainGameMode::AMainGameMode()
{
	// BeginPlay()에선 default pawn class를 정해도 적용되지 않음
	// Level에 Pawn을 배치하고 플레이어 자동 배치를 player0로 하게 되면 default pawn class를 nullptr로 설정해주어야 함
	// 그러지 않으면 pawn이 2개 생성됨 (GameMode, 배치한 pawn)
	DefaultPawnClass = AKnightCharacter::StaticClass();
	PlayerControllerClass = AInGamePlayerController::StaticClass();
	PlayerStateClass = ASeSACPlayerState::StaticClass();

	CMonsterDataManager::GetInst()->Init();
}

void AMainGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	
}

void AMainGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	
}

APlayerController* AMainGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
	const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* Controller = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	int32 JobData = 0;
	if (FParse::Value(*Options, TEXT("Job="), JobData))
	{
		EPlayerJob Job = static_cast<EPlayerJob>(JobData);

		switch (Job) {
		case EPlayerJob::None:
			break;
		case EPlayerJob::Knight:
			DefaultPawnClass = AKnightCharacter::StaticClass();
			UE_LOG(LogTemp, Warning, TEXT("기사 선택"));
			break;
		case EPlayerJob::Archer:
			DefaultPawnClass = AKnightCharacter::StaticClass();
			UE_LOG(LogTemp, Warning, TEXT("궁수 선택"));
			break;
		case EPlayerJob::Magician:
			DefaultPawnClass = AKnightCharacter::StaticClass();
			UE_LOG(LogTemp, Warning, TEXT("마법사 선택"));
			break;
		case EPlayerJob::Gunner:
			DefaultPawnClass = AKnightCharacter::StaticClass();
			UE_LOG(LogTemp, Warning, TEXT("거너 선택"));
			break;
		}
	}

	FString PlayerName = TEXT("Player");
	if (FParse::Value(*Options, TEXT("PlayerName="), PlayerName))
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerName = %s"), *PlayerName);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("MainGameMode Login"));

	USeSACGameInstance* GameInst = GetWorld()->GetGameInstance<USeSACGameInstance>();
	if (IsValid(GameInst))
	{
		GameInst->SetSelectJob((EPlayerJob)JobData);
		GameInst->SetPlayerName(PlayerName);
	}

	return Controller;
}

void AMainGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
