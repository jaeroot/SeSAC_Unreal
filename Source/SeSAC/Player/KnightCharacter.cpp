// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightCharacter.h"

AKnightCharacter::AKnightCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// set CapsuleComponent
	GetCapsuleComponent()->SetCapsuleHalfHeight(95.0f);

	// set Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Skins/Tier2/Kwang_Manban/Meshes/KwangManbun.KwangManbun"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -95.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f ,0.0f));

	// set SpringArm
	mArm->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	mArm->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));
	mArm->TargetArmLength = 500.0f;

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		KwangAnimClass(TEXT("/Game/Player/Knight/ABP_Kwang.ABP_Kwang_C"));
	if (KwangAnimClass.Succeeded())
	{
		GetMesh()->SetAnimClass(KwangAnimClass.Class);
	}
}

void AKnightCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AKnightCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKnightCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
