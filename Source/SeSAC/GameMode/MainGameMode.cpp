// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "../Player/KnightCharacter.h"

AMainGameMode::AMainGameMode()
{
	// BeginPlay()에선 default pawn class를 정해도 적용되지 않음
	// Level에 Pawn을 배치하고 플레이어 자동 배치를 player0로 하게 되면 default pawn class를 nullptr로 설정해주어야 함
	// 그러지 않으면 pawn이 2개 생성됨 (GameMode, 배치한 pawn)
	DefaultPawnClass = AKnightCharacter::StaticClass();
}
