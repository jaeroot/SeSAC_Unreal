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
		
		mIdleAOPitch = PlayerCharacter->GetBaseAimRotation().Pitch;
		mIdleAOYaw = PlayerCharacter->GetBaseAimRotation().Yaw;
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

	OnMontageEnded.AddDynamic(this, &UPlayerAnimInstance::MontageEnd);
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

void UPlayerAnimInstance::PlayAttackMontage()
{
	if (!IsValid(mAttackMontage))
	{
		return;
	}

	if (!mAttackState)
	{
		// 몽타주가 재생중인지 판단
		// 재생중이면 true, 아니면 false
		if (!Montage_IsPlaying(mAttackMontage))
		{
			// InPlayRate : 재생속도
			// MontageLength : 현재 재생된 몽타주의 길이
			// 여기서 다른 몽타주를 재생시켜서 기존 몽타주 재생이 끝날 경우, Ended에 bInterrupted가 true로 들어가게 됨
			// 다른 몽타주 재생이 아닌 실제 몽타주 재생이 끝날 경우, bInterrupted가 false로 들어감
			Montage_SetPosition(mAttackMontage, 0.0f);
			Montage_Play(mAttackMontage);
			Montage_JumpToSection(mAttackSectionArray[mCurrentAttackSection]);
		}
	}
	else
	{
		mAttackCombo = true;
	}

	mAttackState = true;
}

void UPlayerAnimInstance::AnimNotify_AttackCombo()
{
	if (mAttackCombo)	// 콤보 타이밍 전에 공격을 다시 눌렀다면 콤보 공격을 함
	{
		mCurrentAttackSection = (mCurrentAttackSection + 1) % mAttackSectionArray.Num();
		Montage_Play(mAttackMontage);
		Montage_JumpToSection(mAttackSectionArray[mCurrentAttackSection]);

		mAttackCombo = false;
	}
	// else		// 콤보 타이밍까지 공격을 안했다면 공격 종료
	// {
	// 	
	// }
}

void UPlayerAnimInstance::AnimNotify_AttackComboEnd()
{
	if (mCurrentAttackSection < mAttackSectionArray.Num() - 1)
	{
		Montage_SetPosition(mAttackRecoveryMontage, 0.0f);
		Montage_Play(mAttackRecoveryMontage);
		Montage_JumpToSection(mAttackSectionArray[mCurrentAttackSection]);
	}
	else		 // 마지막 모션은 Recovery가 없기 때문에 여기서 초기화
	{
		mAttackCombo = false;
		mAttackState = false;
		mCurrentAttackSection = 0;
	}
}

void UPlayerAnimInstance::MontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == mAttackMontage)
	{
		// 공격의 경우, bInterrupted가 true일 경우, 콤보공격을 하여 이 함수가 들어온 것이고
		// 공격모션이 끝나서 들어올 경우 bInterrupted가 false일 것이기 때문에,
		// false일 경우 Recovery 몽타주를 재생시켜 줌

		// if (!bInterrupted)
		// {
		// 	// 가장 마지막 모션은 Recovery 모션이 합쳐져 있으므로,
		// 	// 가장 마지막 모션을 제외한 다른 모션이 종료될 때만 Recovery 모션을 재생함
		// 	if (mCurrentAttackSection < mAttackSectionArray.Num() - 1)
		// 	{
		// 		Montage_SetPosition(mAttackRecoveryMontage, 0.0f);
		// 		Montage_Play(mAttackRecoveryMontage);
		// 		Montage_JumpToSection(mAttackSectionArray[mCurrentAttackSection]);
		// 	}
		// 	else		 // 마지막 모션은 Recovery가 없기 때문에 여기서 초기화
		// 	{
		// 		mAttackCombo = false;
		// 		mAttackState = false;
		// 		mCurrentAttackSection = 0;
		// 	}
		// }
	}
	else if (Montage == mAttackRecoveryMontage)
	{
		mAttackCombo = false;
		mAttackState = false;
		mCurrentAttackSection = 0;
	}
	
}
