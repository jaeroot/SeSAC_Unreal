// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerAnimInstance.h"
#include "SeSAC/CTest/InputData.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// set CapsuleComponent
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	// set Mesh
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// set SpringArm
	mArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	mArm->SetupAttachment(RootComponent);

	// set Camera
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mArm);

	// set Control Rotation
	bUseControllerRotationYaw = false;
	mArm->bUsePawnControlRotation = true;
	
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	mAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	auto PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		const auto InputData = GetDefault<UDefaultInputData>();
		Subsystem->AddMappingContext(InputData->mDefaultContext, 0);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		// class default object를 얻어옴
		const auto InputData = GetDefault<UDefaultInputData>();
		EnhancedInputComponent->BindAction(InputData->mMove, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveAction);
		EnhancedInputComponent->BindAction(InputData->mRotation, ETriggerEvent::Triggered, this, &APlayerCharacter::RotationAction);
		EnhancedInputComponent->BindAction(InputData->mAttack, ETriggerEvent::Started, this, &APlayerCharacter::AttackAction);
		EnhancedInputComponent->BindAction(InputData->mJump, ETriggerEvent::Started, this, &APlayerCharacter::JumpAction);
		EnhancedInputComponent->BindAction(InputData->mDeath, ETriggerEvent::Started, this, &APlayerCharacter::DeathAction);
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void APlayerCharacter::MoveAction(const FInputActionValue& Value)
{
	FVector Axis = Value.Get<FVector>();
	AddMovementInput(GetActorForwardVector(), Axis.Y);
	AddMovementInput(GetActorRightVector(), Axis.X);

	mAnimInstance->SetMoveDir(Axis);
}

void APlayerCharacter::RotationAction(const FInputActionValue& Value)
{
	FVector Axis = Value.Get<FVector>();
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
}

void APlayerCharacter::AttackAction()
{
	NormalAttack();
}

void APlayerCharacter::JumpAction()
{
	// 물리적으로 jump가 가능할 때만 jump
	if (CanJump())
	{
		Jump();

		mAnimInstance->OnJump();
	}
}

void APlayerCharacter::DeathAction()
{
	mAnimInstance->SetAnimType(EPlayerAnimType::Death);
	GetCharacterMovement()->MaxWalkSpeed = 0;
}

void APlayerCharacter::AttackEnable()
{
}

void APlayerCharacter::AttackDisable()
{
}

void APlayerCharacter::NormalAttack()
{
}

FGenericTeamId APlayerCharacter::GetGenericTeamId() const
{
	return FGenericTeamId(mTeamID);
}

ETeamAttitude::Type APlayerCharacter::GetTeamAttitudeTowards(const AActor& Other) const
{ 
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
	return OtherTeamAgent ? FGenericTeamId::GetAttitude(GetGenericTeamId(), OtherTeamAgent->GetGenericTeamId())
		: ETeamAttitude::Neutral;
}

