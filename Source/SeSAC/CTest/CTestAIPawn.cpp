// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestAIPawn.h"

#include "GameFramework/FloatingPawnMovement.h"

ACTestAIPawn::ACTestAIPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	mBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	SetRootComponent(mBody);
	mBody->SetCapsuleSize(40.0f, 85.0f);
	mBody->SetCollisionProfileName(TEXT("Monster"));

	mMesh= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMesh->SetupAttachment(mBody);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Ranged_Dawn.Minion_Lane_Ranged_Dawn"));
	if (MeshAsset.Succeeded())
	{
		mMesh->SetSkeletalMesh(MeshAsset.Object);
	}
	mMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -85.0f));
	mMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	mMovement->SetUpdatedComponent(mBody);

	SetCanBeDamaged(true);
}

void ACTestAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACTestAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ACTestAIPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	// CanbeDamage가 false일 경우 이 함수는 0을 반환함
	// true일 경우 Damage를 반환함
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	mHP -= DamageAmount;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Damage : %.5f"), DamageAmount));

	if (mHP <= 0.0f)
	{
		Destroy();
	}
	
	return DamageAmount;
}