// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCharacter.h"

AMazeCharacter::AMazeCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set Spring Arm
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	SpringArmComponent->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));
	SpringArmComponent->TargetArmLength = 500.0f;

}

void AMazeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMazeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMazeCharacter::MoveAction(const FInputActionValue& Value)
{
}

void AMazeCharacter::RotationAction(const FInputActionValue& Value)
{
}

void AMazeCharacter::AttackAction()
{
}

void AMazeCharacter::ShieldAction()
{
}

