// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "SeSAC/CTest/InputData.h"

AMazeCharacter::AMazeCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set Spring Arm
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	SpringArmComponent->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));
	SpringArmComponent->TargetArmLength = 500.0f;

	// Set Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
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
	SpringArmComponent->bUsePawnControlRotation = true;

	// Set Rotation Scene Component
	RotationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RotationComponent"));
	RotationComponent->SetupAttachment(RootComponent);

	// Set Rotating Movement Component
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovementComponent->RotationRate = { 0.0f, 180.0f, 0.0f};
	RotatingMovementComponent->SetUpdatedComponent(RotationComponent);

	// Set Anim Blueprint
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		GideonAnim(TEXT("/Game/ParagonGideon/Characters/Heroes/Gideon/Gideon_AnimBlueprint.Gideon_AnimBlueprint_C"));
	if (GideonAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(GideonAnim.Class);
	}

	// Set Attack Class
	static ConstructorHelpers::FClassFinder<AActor>
		AttackClassActor(TEXT("/Game/Test/TestBlueprint/BP_TestActor.BP_TestActor_C"));
	if (AttackClassActor.Succeeded())
	{
		AttackClass = AttackClassActor.Class;
	}

	// Set Shield Class
	static ConstructorHelpers::FClassFinder<AActor>
		ShieldClassActor(TEXT("/Game/Test/TestBlueprint/BP_TestShield.BP_TestShield_C"));
	if (ShieldClassActor.Succeeded())
	{
		ShieldClass = ShieldClassActor.Class;
	}
	
	// Set Collision Channel
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
}

void AMazeCharacter::BeginPlay()
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
}

void AMazeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 사용 불가능 상태일때 시간 계산
	if (!bShieldEnable)
	{
		ShieldTime += DeltaTime;

		if (ShieldTime >= 5.0f)
		{
			bShield = false;
		}

		if (ShieldTime >= ShieldCoolDown)
		{
			RotatingMovementComponent->Deactivate();
			bShieldEnable = true;
		}
	}
}

void AMazeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		// class default object를 얻어옴
		const auto InputData = GetDefault<UTestInputData>();
		EnhancedInputComponent->BindAction(InputData->mMove, ETriggerEvent::Triggered, this, &AMazeCharacter::MoveAction);
		EnhancedInputComponent->BindAction(InputData->mRotation, ETriggerEvent::Triggered, this, &AMazeCharacter::RotationAction);
		EnhancedInputComponent->BindAction(InputData->mAttack, ETriggerEvent::Started, this, &AMazeCharacter::AttackAction);
		EnhancedInputComponent->BindAction(InputData->mShield, ETriggerEvent::Started, this, &AMazeCharacter::ShieldAction);
	}
}

void AMazeCharacter::MoveAction(const FInputActionValue& Value)
{
	FVector Axis = Value.Get<FVector>();
	AddMovementInput(GetActorForwardVector(), Axis.Y);
	AddMovementInput(GetActorRightVector(), Axis.X);
}

void AMazeCharacter::RotationAction(const FInputActionValue& Value)
{
	FVector Axis = Value.Get<FVector>();
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
}

void AMazeCharacter::AttackAction()
{
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
	FVector Loc = GetActorLocation() + GetActorForwardVector() * 100;
	FRotator Rot = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(AttackClass, Loc, Rot, Param);

	auto Montage = LoadObject<UAnimMontage>(nullptr, TEXT("/Script/Engine.AnimMontage'/Game/ParagonGideon/Characters/Heroes/Gideon/Animations/Primary_Attack_A_Medium_Montage.Primary_Attack_A_Medium_Montage'"));	
	PlayAnimMontage(Montage);
}

void AMazeCharacter::ShieldAction()
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
	RotatingMovementComponent->Activate();
	bShield = true;

	// Relative Transform
	if (!ShieldClass)
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
		
		auto SpawnActor = GetWorld()->SpawnActor<AActor>(ShieldClass, Loc, Rot, Param);
		if (IsValid(SpawnActor) && RotationComponent)
		{
			SpawnActor->AttachToComponent(RotationComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}

