// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SelectPawn.h"
#include "SeSAC/CTest/InputData.h"

// Sets default values
ASelectPlayer::ASelectPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mRoot);
}

// Called when the game starts or when spawned
void ASelectPlayer::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI Mode;
	GetController<APlayerController>()->SetInputMode(Mode);
	GetController<APlayerController>()->SetShowMouseCursor(true);
	
	auto PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		const auto InputData = GetDefault<USelectInputData>();
		Subsystem->AddMappingContext(InputData->mDefaultContext, 0);
	}
}

// Called every frame
void ASelectPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult result;
	bool Collision = GetController<APlayerController>()->GetHitResultUnderCursor(ECC_Visibility, false, result);

	if (Collision)
	{
		
		ASelectPawn* SelectPawn = Cast<ASelectPawn>(result.GetActor());
		if (IsValid(SelectPawn))
		{
			if (mOnMouseActor && mOnMouseActor != SelectPawn)
			{
				mOnMouseActor->OnMouse(false);
			}			
			mOnMouseActor = SelectPawn;

			mOnMouseActor->OnMouse(true);
		}
	}
	else
	{
		if (mOnMouseActor)
		{
			mOnMouseActor->OnMouse(false);
		}
		mOnMouseActor = nullptr;
	}
}

// Called to bind functionality to input
void ASelectPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		// class default object를 얻어옴
		const auto InputData = GetDefault<USelectInputData>();
		EnhancedInputComponent->BindAction(InputData->mSelect, ETriggerEvent::Started, this, &ASelectPlayer::ClickAction);
	}
}

void ASelectPlayer::ClickAction(const FInputActionValue& Value)
{
	if (!IsValid(mOnMouseActor))
	{
		return;
	}

	FString Option = FString::Printf(TEXT("Job=%d"), static_cast<int32>(mOnMouseActor->GetJob()));

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"), true, Option);
}

