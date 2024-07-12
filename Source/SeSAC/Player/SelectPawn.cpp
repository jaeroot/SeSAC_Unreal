// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPawn.h"

#include "SeSAC/CTest/InputData.h"

// Sets default values
ASelectPawn::ASelectPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	mCapsule->SetCapsuleSize(35.0f, 95.0f);
	SetRootComponent(mCapsule);

	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -95.0f));
	mMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	mMesh->SetupAttachment(mCapsule);
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AutoPossessAI = EAutoPossessAI::Disabled;
}

// Called when the game starts or when spawned
void ASelectPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASelectPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASelectPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

void ASelectPawn::OnMouse(bool Overlap)
{
	mMesh->SetRenderCustomDepth(Overlap);
}

