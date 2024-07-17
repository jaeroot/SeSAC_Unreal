// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"

void UStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	mExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));

	mStartButton->OnClicked.AddDynamic(this, &UStartWidget::StartClick);
	mStartButton->OnHovered.AddDynamic(this, &UStartWidget::StartHovered);
	mStartButton->OnUnhovered.AddDynamic(this, &UStartWidget::StartUnHovered);
	
	mExitButton->OnClicked.AddDynamic(this, &UStartWidget::ExitClick);
	mExitButton->OnHovered.AddDynamic(this, &UStartWidget::ExitHovered);
	mExitButton->OnUnhovered.AddDynamic(this, &UStartWidget::ExitUnHovered);

	// Animation을 얻어옴
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();

	// int32 AnimCount = WidgetClass->Animations.Num();
	for (auto Animation : WidgetClass->Animations)
	{
		FString Name = Animation->GetName();

		mAnimMap.Add(Name, Animation);

		UE_LOG(LogTemp, Warning, TEXT("Name : %s"), *Name);
	}

	UWidgetAnimation* Anim = mAnimMap.FindRef("StartAnim_INST");
	if (IsValid(Anim))
	{
		PlayAnimation(Anim);
	}
}

void UStartWidget::StartClick()
{
	if (!mNextLevelName.IsNone())
	{
		UGameplayStatics::OpenLevel(GetWorld(), mNextLevelName);
	}
}

void UStartWidget::StartHovered()
{
	UWidgetAnimation* Anim = mAnimMap.FindRef("StartButtonScale_INST");
	if (IsValid(Anim))
	{
		PlayAnimation(Anim);
	}
}

void UStartWidget::StartUnHovered()
{
	UWidgetAnimation* Anim = mAnimMap.FindRef("StartButtonScale_INST");
	if (IsValid(Anim))
	{
		// PlayAnimation(Anim, 0.0f, 1, EUMGSequencePlayMode::Reverse);
		PlayAnimationReverse(Anim);
	}
}

void UStartWidget::ExitClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UStartWidget::ExitHovered()
{
	UWidgetAnimation* Anim = mAnimMap.FindRef("ExitButtonScale_INST");
	if (IsValid(Anim))
	{
		PlayAnimation(Anim);
	}
}

void UStartWidget::ExitUnHovered()
{
	UWidgetAnimation* Anim = mAnimMap.FindRef("ExitButtonScale_INST");
	if (IsValid(Anim))
	{
		// PlayAnimation(Anim, 0.0f, 1, EUMGSequencePlayMode::Reverse);
		PlayAnimationReverse(Anim);
	}
}
