// Fill out your copyright notice in the Description page of Project Settings.


#include "InputData.h"

UDefaultInputData::UDefaultInputData()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext>
			Asset(TEXT("/Game/Input/IMC_Default.IMC_Default"));
		if (Asset.Succeeded())
		{
			mDefaultContext = Asset.Object;
		}
	}
	
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Game/Input/IA_Move.IA_Move"));
		if (Asset.Succeeded())
		{
			mMove = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Game/Input/IA_Rotation.IA_Rotation"));
		if (Asset.Succeeded())
		{
			mRotation = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Game/Input/IA_Attack.IA_Attack"));
		if (Asset.Succeeded())
		{
			mAttack = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Game/Input/IA_Jump.IA_Jump"));
		if (Asset.Succeeded())
		{
			mJump = Asset.Object;
		}
	}
}

UTestInputData::UTestInputData()
{
	{
		// 언리얼 에셋을 불러올때 사용
		static ConstructorHelpers::FObjectFinder<UInputMappingContext>
			Asset(TEXT("/Game/Test/TestInput/IMC_Test.IMC_Test"));

		// 정상적으로 로딩했는지 판단
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정
			mDefaultContext = Asset.Object;
		}
	}
	
	{
		// 언리얼 에셋을 불러올때 사용
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Game/Test/TestInput/IA_TestMove.IA_TestMove"));

		// 정상적으로 로딩했는지 판단
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정
			mMove = Asset.Object;
		}
	}

	{
		// 언리얼 에셋을 불러올때 사용
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Game/Test/TestInput/IA_TestRotation.IA_TestRotation"));

		// 정상적으로 로딩했는지 판단
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정
			mRotation = Asset.Object;
		}
	}

	{
		// 언리얼 에셋을 불러올때 사용
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Game/Test/TestInput/IA_TestAttack.IA_TestAttack"));

		// 정상적으로 로딩했는지 판단
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정
			mAttack = Asset.Object;
		}
	}

	{
		// 언리얼 에셋을 불러올때 사용
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Game/Test/TestInput/IA_TestShield.IA_TestShield"));

		// 정상적으로 로딩했는지 판단
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정
			mShield = Asset.Object;
		}
	}
	
	{
		// 언리얼 에셋을 불러올때 사용
		static ConstructorHelpers::FObjectFinder<UInputAction>
			Asset(TEXT("/Game/Test/TestInput/IA_TripleShot.IA_TripleShot"));

		// 정상적으로 로딩했는지 판단
		if (Asset.Succeeded())
		{
			// 성공했을 경우 불러온 에셋을 멤버변수에 지정
			mTripleShot = Asset.Object;
		}
	}
}
