// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestPlayerCharacter.h"

#include "CTestShield.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputData.h"
#include "GameFramework/RotatingMovementComponent.h"

ACTestPlayerCharacter::ACTestPlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	// Set Spring Arm
	mArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	mArm->SetupAttachment(RootComponent);
	mArm->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	mArm->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));
	mArm->TargetArmLength = 500.0f;

	// Set Camera
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mArm);

	// Set Capsule Component
	GetCapsuleComponent()->SetCapsuleSize(34.0f, 94.0f);
	
	// Set Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Undertow/Meshes/Gideon_Undertow.Gideon_Undertow"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -94.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Set Control Rotation
	bUseControllerRotationYaw = true;
	mArm->bUsePawnControlRotation = true;
	
	// Set Rotation Scene Component
	mRotation = CreateDefaultSubobject<USceneComponent>(TEXT("Rotation"));
	mRotation->SetupAttachment(RootComponent);

	// Set Rotating Movement Component
	mRotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	mRotatingMovementComponent->RotationRate = { 0.0f, 180.0f, 0.0f};
	mRotatingMovementComponent->SetUpdatedComponent(mRotation);

	// Set Anim Blueprint
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		GideonAnim(TEXT("/Game/ParagonGideon/Characters/Heroes/Gideon/Gideon_AnimBlueprint.Gideon_AnimBlueprint_C"));
	if (GideonAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(GideonAnim.Class);
	}

	// FClassFinder를 이용하여 클래스 정보를 읽어오고자 하면, 경로의 뒤에 반드시 _C를 붙여주어야 함
	static ConstructorHelpers::FClassFinder<AActor>
		AttackClass(TEXT("/Game/Test/TestBlueprint/BP_TestActor.BP_TestActor_C"));
	if (AttackClass.Succeeded())
	{
		mAttackClass = AttackClass.Class;
	}
}

void ACTestPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 현재 캐릭터에 빙의되어 있는 컨트롤러가 PlayerController가 맞는지 확인하고,
	// 맞다면 EnhancedInputSubsystem을 얻어오게 됨
	auto PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		const auto InputData = GetDefault<UTestInputData>();
		Subsystem->AddMappingContext(InputData->mDefaultContext, 0);
	}


	mShieldClass = LoadClass<AActor>(nullptr, TEXT("/Game/Test/TestBlueprint/BP_TestShield.BP_TestShield_C"));
}

void ACTestPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 사용 불가능 상태일때 시간 계산
	if (!bShieldEnable)
	{
		ShieldTime += DeltaTime;

		if (ShieldTime >= ShieldCoolDown)
		{
			mRotatingMovementComponent->Deactivate();
			bShieldEnable = true;
		}
	}
}

void ACTestPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		// class default object를 얻어옴
		const auto InputData = GetDefault<UTestInputData>();
		EnhancedInputComponent->BindAction(InputData->mMove, ETriggerEvent::Triggered, this, &ACTestPlayerCharacter::MoveAction);
		EnhancedInputComponent->BindAction(InputData->mRotation, ETriggerEvent::Triggered, this, &ACTestPlayerCharacter::RotationAction);
		EnhancedInputComponent->BindAction(InputData->mAttack, ETriggerEvent::Started, this, &ACTestPlayerCharacter::AttackAction);
		EnhancedInputComponent->BindAction(InputData->mShield, ETriggerEvent::Started, this, &ACTestPlayerCharacter::ShieldAction);
		EnhancedInputComponent->BindAction(InputData->mTripleShot, ETriggerEvent::Started, this, &ACTestPlayerCharacter::TripleShotAction);
	}
}

void ACTestPlayerCharacter::MoveAction(const FInputActionValue& Value)
{
	FVector Axis = Value.Get<FVector>();
	AddMovementInput(GetActorForwardVector(), Axis.Y);
	AddMovementInput(GetActorRightVector(), Axis.X);
}

void ACTestPlayerCharacter::RotationAction(const FInputActionValue& Value)
{
	FVector Axis = Value.Get<FVector>();
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
	
	// AddOnScreenDebugMessage : 뷰포트에 원하는 문자열을 출력해주는 함수
	// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, FString::Printf(TEXT("X : %f, y : %f"), Axis.X, Axis.Y));

	// GetWorld는 생성자에서 사용 불가
	// GetWorld()->GetDeltaSeconds();
}

void ACTestPlayerCharacter::AttackAction()
{
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
	FVector Loc = GetActorLocation() + GetActorForwardVector() * 100;
	FRotator Rot = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(mAttackClass, Loc, Rot, Param);
	// GetWorld()->SpawnActor<ACTestPlayerPawn>(GetActorLocation(), GetActorRotation());
}

void ACTestPlayerCharacter::ShieldAction()
{
	// 사용 불가능 상태일 경우 처리 없이 반환
	if (!bShieldEnable)
	{
		return;
	}

	// 사용 불가능 상태로 만들어줌
	bShieldEnable = false;
	// 시간 계산을 시작해야 하기 때문에 0으로 초기화
	ShieldTime = 0.0f;
	mRotatingMovementComponent->Activate();

	// Relative Transform
	if (!mShieldClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unidentified Shield Class"));
		return;
	}
	
	constexpr int ShieldCount = 4;
	constexpr float ShieldRange = 200.0f;
	
	static int ShieldForward[ShieldCount] = { 1, 0, -1, 0 };
	static int ShieldRight[ShieldCount] = { 0, 1, 0, -1 };
	
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
	
	for (int i = 0; i < ShieldCount; i++)
	{
		FVector Loc = { ShieldForward[i] * ShieldRange, ShieldRight[i] * ShieldRange, 0.0f };
		FRotator Rot = { 0.0f, 90.0f * i, 0.0f };
		
		auto SpawnActor = GetWorld()->SpawnActor<AActor>(mShieldClass, Loc, Rot, Param);
		if (IsValid(SpawnActor) && mRotation)
		{
			SpawnActor->AttachToComponent(mRotation, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}


	// World Transform
	// for (int32 i = 0; i < 4; i++)
	// {
	// 	FVector Location;
	// 	FRotator Rot = FRotator::ZeroRotator;
	// 	
	// 	switch (i)
	// 	{
	// 	case 0:
	// 		Location = GetActorLocation() + GetActorForwardVector() * 200.0f;
	// 		break;
	// 	case 1:
	// 		Location = GetActorLocation() + GetActorRightVector() * 200.0f;
	// 		Rot.Yaw = 90.0f;
	// 		break;
	// 	case 2:
	// 		Location = GetActorLocation() + GetActorForwardVector() * -200.0f;
	// 		Rot.Yaw = 180.0f;
	// 		break;
	// 	case 3:
	// 		Location = GetActorLocation() + GetActorRightVector() * -200.0f;
	// 		Rot.Yaw = 270.0f;
	// 		break;
	// 	default:
	// 		break;
	// 	}
	//
	// 	FActorSpawnParameters Param;
	// 	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
	//
	// 	// ACTestShield::StaticClass() : UClass 정보를 꺼내옴
	// 	auto Shield = GetWorld()->SpawnActor<ACTestShield>(ACTestShield::StaticClass(), Location, GetActorRotation() + Rot, Param);
	// 	Shield->AttachToComponent(mRotation, FAttachmentTransformRules::KeepWorldTransform);
	// }
}

void ACTestPlayerCharacter::TripleShotAction()
{
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
	for (int i = -1; i <= 1; i++)
	{
		FVector Loc = GetActorLocation() + GetActorForwardVector() * 100;
		Loc += GetActorRightVector() * 50 * i;
		
		FRotator Rot = GetActorRotation();
		Rot.Yaw += 10.0f * i;
		
		GetWorld()->SpawnActor<AActor>(mAttackClass, Loc, Rot, Param);
	}
}
