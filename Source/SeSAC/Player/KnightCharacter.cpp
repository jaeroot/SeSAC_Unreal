// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightCharacter.h"

#include "PlayerAnimInstance.h"

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

	// static ConstructorHelpers::FClassFinder<UAnimInstance>
	// 	KwangAnimClass(TEXT("/Game/Player/Knight/ABP_Kwang.ABP_Kwang_C"));
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		KwangAnimClass(TEXT("/Game/Player/Knight/ABP_Kwang_TemplateLink.ABP_Kwang_TemplateLink_C"));
	if (KwangAnimClass.Succeeded())
	{
		GetMesh()->SetAnimClass(KwangAnimClass.Class);
	}

	// set WeaponBox
	mWeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox"));
	mWeaponBox->SetupAttachment(GetMesh(), TEXT("weapon_r_collision"));
	mWeaponBox->SetBoxExtent(FVector(3.0, 65.0, 15.0));
	mWeaponBox->SetCollisionProfileName(TEXT("PlayerAttackOverlap"));
	mWeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		HitAsset(TEXT("/Game/ParagonKwang/FX/Particles/Abilities/Primary/FX/P_Kwang_Primary_Impact.P_Kwang_Primary_Impact"));
	if (HitAsset.Succeeded())
	{
		mNormalAttackHit = HitAsset.Object;
	}

	// mWeaponBox->SetNotifyRigidBodyCollision(true);
}

void AKnightCharacter::BeginPlay()
{
	Super::BeginPlay();

	// mWeaponBox->OnComponentHit.AddDynamic(this, &AKnightCharacter::WeaponHit);
	mWeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AKnightCharacter::WeaponBeginOverlap);
}

void AKnightCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKnightCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AKnightCharacter::AttackEnable()
{
	mWeaponBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	FVector Start = GetActorLocation() + GetActorForwardVector() * 50.0f;
	FVector End = Start + GetActorForwardVector() * 200.0f;
	FCollisionQueryParams Param;
	Param.AddIgnoredActor(this);
	TArray<FHitResult> Results;
	bool Collision = GetWorld()->SweepMultiByChannel(
		Results,
		Start,
		End,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel7,
		FCollisionShape::MakeSphere(50.0f),
		Param
	);

#if ENABLE_DRAW_DEBUG

	FColor DrawColor = Collision ? FColor::Red : FColor::Green;
	DrawDebugCapsule(
		GetWorld(),
		(Start + End) / 2,
		100.0f,
		50.0f,
		FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor,
		false,
		2.0f
	);
	
#endif
	
	if (Collision)
	{
		// 배열 개수만큼 반복하여 하나씩 Result에 꺼내옴
		for (auto Result: Results)
		{
			FDamageEvent DmgEvent;
			Result.GetActor()->TakeDamage(10.0f, DmgEvent, GetController(), this);

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mNormalAttackHit,
				Result.ImpactPoint, Result.ImpactNormal.Rotation(), true);

			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan,
				FString::Printf(TEXT("Weapon Hit : %s"), *Result.GetActor()->GetName()));
		}	
	}
}

void AKnightCharacter::AttackDisable()
{
	mWeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AKnightCharacter::NormalAttack()
{
	mAnimInstance->PlayAttackMontage();
}

void AKnightCharacter::WeaponHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan,
		FString::Printf(TEXT("Weapon Hit : %s"), *OtherActor->GetName()));
}

void AKnightCharacter::WeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FDamageEvent DmgEvent;
	OtherActor->TakeDamage(10.0f, DmgEvent, GetController(), this);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mNormalAttackHit,
		OtherActor->GetActorLocation(), OtherActor->GetActorRotation(), true);
	
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan,
		FString::Printf(TEXT("Impact Point : %s, Normal : %s"),
			*SweepResult.ImpactPoint.ToString(),
			*SweepResult.ImpactNormal.ToString()));
}
