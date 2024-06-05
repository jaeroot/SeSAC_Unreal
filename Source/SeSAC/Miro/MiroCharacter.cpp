// Fill out your copyright notice in the Description page of Project Settings.


#include "MiroCharacter.h"

AMiroCharacter::AMiroCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set Spring Arm
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	SpringArmComponent->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));
	SpringArmComponent->TargetArmLength = 500.0f;

}

void AMiroCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMiroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMiroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMiroCharacter::MoveAction(const FInputActionValue& Value)
{
}

void AMiroCharacter::RotationAction(const FInputActionValue& Value)
{
}

void AMiroCharacter::AttackAction()
{
}

void AMiroCharacter::ShieldAction()
{
}

