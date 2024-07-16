// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SelectPawn.h"
#include "Blueprint/UserWidget.h"
#include "Select/SelectPlayerAnimTemplate.h"
#include "SeSAC/CTest/InputData.h"
#include "SeSAC/UI/CharactertSelect/CharacterSelectWidget.h"

// Sets default values
ASelectPlayer::ASelectPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mRoot);

	static ConstructorHelpers::FClassFinder<UCharacterSelectWidget>
		WidgetClass(TEXT("/Game/UI/CharacterSelect/WB_CharacterSelect.WB_CharacterSelect_C"));
	if (WidgetClass.Succeeded())
	{
		mWidgetClass = WidgetClass.Class;
	}
}

// Called when the game starts or when spawned
void ASelectPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(mWidgetClass))
	{
		mWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(), mWidgetClass);

		if (IsValid(mWidget))
		{
			mWidget->AddToViewport();
		}
	}
	

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
		else
		{
			if (mOnMouseActor)
			{
				mOnMouseActor->OnMouse(false);
			}
			mOnMouseActor = nullptr;
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
	mOnSelectPawn = mOnMouseActor;

	mWidget->SetSelectPawn(mOnSelectPawn);
	
	if (mOnMouseActor)
	{
		// mWidget->StartButtonEnable(true);
		// mOnMouseActor->ChangeAnim(ESelectPlayerAnim::Select);

		// int32 Index = static_cast<int32>(mOnSelectPawn->GetJob());
		// --Index;

		int32 Index = -1;
		switch (mOnSelectPawn->GetJob()) {
		case EPlayerJob::None:
			Index = 0;
			break;
		case EPlayerJob::Knight:
			Index = 0;
			break;
		case EPlayerJob::Archer:
			Index = 0;
			break;
		case EPlayerJob::Magician:
			Index = 1;
			break;
		case EPlayerJob::Gunner:
			Index = 0;
			break;
		}
		
		GetController<APlayerController>()->SetViewTargetWithBlend(mCameraTransitionArray[Index], 2.0f, VTBlend_Cubic);

		if (mTransitionTimer.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(mTransitionTimer);
		}

		GetWorld()->GetTimerManager().SetTimer(mTransitionTimer, this, &ASelectPlayer::TransitionEnd, 2.0f);
	
	}
	else
	{
		mWidget->StartButtonEnable(false);
		
		if (mTransitionTimer.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(mTransitionTimer);
		}
		
		GetController<APlayerController>()->SetViewTargetWithBlend(this, 2.0f, VTBlend_Cubic);

	}
	
	// if (!IsValid(mOnMouseActor))
	// {
	// 	return;
	// }
	//
	// FString Option = FString::Printf(TEXT("Job=%d"), static_cast<int32>(mOnMouseActor->GetJob()));
	//
	// UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"), true, Option);
}

void ASelectPlayer::TransitionEnd()
{
	mWidget->StartButtonEnable(true);
	
	mOnSelectPawn->ChangeAnim(ESelectPlayerAnim::Select);

	GetWorld()->GetTimerManager().ClearTimer(mTransitionTimer);
}

