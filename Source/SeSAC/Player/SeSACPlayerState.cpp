// Fill out your copyright notice in the Description page of Project Settings.


#include "SeSACPlayerState.h"

#include "InGamePlayerController.h"
#include "SeSAC/SeSACGameInstance.h"

UDataTable* ASeSACPlayerState::mPlayerInfoTable = nullptr;

ASeSACPlayerState::ASeSACPlayerState()
{
	if (!mPlayerInfoTable)
	{
		static ConstructorHelpers::FObjectFinder<UDataTable>
			InfoTableAsset(TEXT("/Game/Player/DT_PlayerInfo.DT_PlayerInfo"));
		if (InfoTableAsset.Succeeded())
		{
			mPlayerInfoTable = InfoTableAsset.Object;
		}
	}
}

void ASeSACPlayerState::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PlayerState BeginPlay"));

	USeSACGameInstance* GameInst = GetWorld()->GetGameInstance<USeSACGameInstance>();
	if (IsValid(GameInst))
	{
		EPlayerJob SelectJob = GameInst->GetSelectJob();
		FString PlayerName = GameInst->GetPlayerName();

		mName = PlayerName;
		mJob = SelectJob;

		AInGamePlayerController* Controller = GetPawn()->GetController<AInGamePlayerController>();
		if (IsValid(Controller))
		{
			Controller->SetPlayerName(mName);
		}

		// 데이터 테이블에서 나머지 정보를 얻어옴
		if (IsValid(mPlayerInfoTable))
		{
			FName RowName;

			switch (SelectJob) {
			case EPlayerJob::None:
				RowName = TEXT("Knight");
				break;
			case EPlayerJob::Knight:
				RowName = TEXT("Knight");
				break;
			case EPlayerJob::Archer:
				RowName = TEXT("Archer");
				break;
			case EPlayerJob::Magician:
				RowName = TEXT("Magician");
				break;
			case EPlayerJob::Gunner:
				RowName = TEXT("Gunner");
				break;
			default:
				break;
			}
			
			const FPlayerInfo* Info = mPlayerInfoTable->FindRow<FPlayerInfo>(RowName, TEXT(""));

			if (Info)
			{
				mLevel = 1;
				mExp = 0;
				mGold = 10000;
				mAttack = Info->mAttack;
				mDefense = Info->mDefense;
				mHP = Info->mHP;
				mHPMax = Info->mHP;
				mMP = Info->mMP;
				mMPMax = Info->mMP;
				mMoveSpeed = Info->mMoveSpeed;
				mAttackDistance = Info->mAttackDistance;
			}
		}
	}
	
}

void ASeSACPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

bool ASeSACPlayerState::Damage(float Attack)
{
	float Dmg = Attack - mDefense;
	Dmg = Dmg < 1.0f ? 1.0f : Dmg;
	
	mHP -= Dmg;

	bool result = false;

	if (mHP <= 0.0f)
	{
		mHP = 0.0f;
		result = true;
	}

	if (mHPDelegate.IsBound())
	{
		float Percent = mHP / mHPMax;
		mHPDelegate.Broadcast(Percent);
	}
	
	// AInGamePlayerController* Controller = GetPawn()->GetController<AInGamePlayerController>();
	// if (IsValid(Controller))
	// {
	// 	float Percent = mHP / mHPMax;
	// 	Controller->SetHPPercent(Percent);
	// }
	
	return result;
}
