// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Pawn.h"
#include "SelectPlayer.generated.h"

class UCharacterSelectWidget;
struct FInputActionValue;

UCLASS()
class SESAC_API ASelectPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASelectPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void ClickAction(const FInputActionValue& Value);

	UFUNCTION()
	void TransitionEnd();

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera;

	class ASelectPawn* mOnMouseActor;
	class ASelectPawn* mOnSelectPawn = nullptr;

	TSubclassOf<UCharacterSelectWidget> mWidgetClass;
	UCharacterSelectWidget* mWidget;
	
	UPROPERTY(EditAnywhere)
	TArray<AActor*> mCameraTransitionArray;

	FTimerHandle mTransitionTimer;
};
