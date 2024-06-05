// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Pawn.h"
#include "CTestPlayerPawn.generated.h"

// class UCameraComponent;

UCLASS()
class SESAC_API ACTestPlayerPawn : public APawn
{
	GENERATED_BODY()		// 언리얼이 가져야할 기능들을 자동으로 추가해주는 매크로

public:
	ACTestPlayerPawn();

	// 매 frame마다 호출되는 함수
	// DeltaTime - 한 frame이 동작할때 흐른 시간을 의미함
	virtual void Tick(float DeltaTime) override;
	// 키를 눌렀을 때 작동해야 하는 함수 포인터를 저장해두고, 해당 함수에선 기능을 만듦
	// 대신 전역 함수가 아닌 UObject 함수를 저장해야 함
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// 플레이가 시작될때 객체마다 1번씩만 호출되는 함수
	// 액터가 준비가 된 후에 호출됨
	virtual void BeginPlay() override;

protected:
	// UObject들은 Reference Counter가 들어간 Smart Pointer기능이 들어가 있음
	// UPROPERTY : 언리얼 오브젝트 클래스에서 사용할 수 있는 기능
	// 클래스의 멤버변수마다 사용 가능
	// 에디터와 연결되는 등의 특수한 옵션 설정을 해줄 때 사용
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mMesh;
	// TObjectPtr<UStaticMeshComponent> mMesh1;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera;

};
