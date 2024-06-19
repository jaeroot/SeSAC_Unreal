// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "PlayerCharacter.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// Cast : 타입이 맞지 않으면 nullptr 반환
	auto PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	// 형변환하여 얻어온 객체가 유효할 경우
	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();
		
		if (IsValid(Movement))
		{
			mMoveSpeed = Movement->Velocity.Length();
			mAcceleration = Movement->GetCurrentAcceleration().Length() > 0.0f;
			mIsAir = Movement->IsFalling();
		}
	}
}

void UPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UPlayerAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UPlayerAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UPlayerAnimInstance::SetMoveDir(const FVector& ActionValue)
{
	mMoveDir = 0.0f;

	if (ActionValue.Y > 0.0f)
	{
		if (ActionValue.X > 0.0f)
		{
			mMoveDir = 45.0f;
		}
		else if (ActionValue.X < 0.0f)
		{
			mMoveDir = -45.0f;
		}
	}
	if (ActionValue.Y < 0.0f)
	{
		if (ActionValue.X > 0.0f)
		{
			mMoveDir = 135.0f;
		}
		else if (ActionValue.X < 0.0f)
		{
			mMoveDir = -135.0f;
		}
		else
		{
			mMoveDir = 180.0f;
		}
	}
	else
	{
		if (ActionValue.X > 0.0f)
		{
			mMoveDir = 90.0f;
		}
		else if (ActionValue.X < 0.0f)
		{
			mMoveDir = -90.0f;
		}
	}
}
