// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestBullet.h"

#include "GameFramework/ProjectileMovementComponent.h"

ACTestBullet::ACTestBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<USphereComponent>(TEXT("Body"));
	SetRootComponent(mBody);
	mBody->SetSphereRadius(50.0f);
	mBody->SetCollisionProfileName(TEXT("PlayerAttack"));

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetupAttachment(mBody);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Game/Test/TestMesh/Sphere.Sphere"));
	if (MeshAsset.Succeeded())
	{
		mMesh->SetStaticMesh(MeshAsset.Object);
	}
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	mMovement->SetUpdatedComponent(mBody);
	mMovement->InitialSpeed = 1500.0f;
	mMovement->ProjectileGravityScale = 0.1f;
	// mMovement->bShouldBounce = true;
}

void ACTestBullet::BeginPlay()
{
	Super::BeginPlay();

	mMovement->OnProjectileStop.AddDynamic(this, &ACTestBullet::ProjectileHit);

	mPrevLocation = GetActorLocation();
}

void ACTestBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 현재 프레임의 위치
	FVector Location = GetActorLocation();

	// 현재 프레임과 이전 프레임 위치 사이의 거리를 구함
	float Distance = FVector::Distance(Location, mPrevLocation);
	// FVector Dir = Location - mPrevLocation;
	// float Distance = Dir.Length();
	mDistance -= Distance;

	if (mDistance <= 0.0f)
	{
		Destroy();
	}
	
	mPrevLocation = Location;
}

void ACTestBullet::ProjectileHit(const FHitResult& HitResult)
{
	// 동기화된 방식
	// UParticleSystem : 캐스케이드 파티클 시스템 에셋 타입
	// LoadObject : 참조 없는 애셋을 로딩하고 참조할 때 사용
	auto Particle = LoadObject<UParticleSystem>(GetWorld(), TEXT("/Game/AdvancedMagicFX13/Particles/P_ky_burst.P_ky_burst"));
	
	// IsValid : 유효성 체크. UObject 객체가 유효한 객체인지 판단해줌
	if (IsValid(Particle))
	{
		// HitResult.ImpactPoint : 충돌 위치
		// GameplayStatics : 게임 플레이 도중에 사용할 수 있는 유용한 함수들 제공
		// SpawnEmitterAtLocation : 위치에 소환, SpawnEmitterAttached : 부착한 위치에 소환
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), true);
		
		GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Red, HitResult.ImpactNormal.ToString());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Red, TEXT("Particle None"));
	}

	// ImpactNormal : 방향 벡터, rotation으로 바꿀 수 있음
	// auto destroy : 파티클 끝나면 월드에서 제거해줌
	
	// // FindObject : 참조 있는 애셋을 참조할 때 사용
	// auto Particle = FindObject<UParticleSystem>(GetWorld(), TEXT("/Game/AdvancedMagicFX13/Particles/P_ky_burst.P_ky_burst"));
	//
	// if (!IsValid(Particle))
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Red, TEXT("Particle None"));
	// 	Particle = LoadObject<UParticleSystem>(GetWorld(), TEXT("/Game/AdvancedMagicFX13/Particles/P_ky_burst.P_ky_burst"));
	// }
	// else
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Red, TEXT("Particle"));
	// }
	
	
	// play sound 2d : 어디서 듣던 같음
	// play sound at location : 3d sound, 공간 음향, 소리 감쇠
	auto Sound = LoadObject<USoundBase>(GetWorld(), TEXT("/Game/Sound/Fire1.Fire1"));

	if (IsValid(Sound))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, HitResult.ImpactNormal);
	}
	

	// 충돌된 Actor의 TakeDamage 함수 호출
	// 이 함수가 재정의 되어 있다면 재정의된 함수가 호출될 것이므로
	// 재정의된 함수에서 처리를 할 수 있다.
	FDamageEvent DmgEvent;
	// FRadialDamageEvent DmgEvent;		방사형 데미지
	HitResult.GetActor()->TakeDamage(mDamage, DmgEvent, mOwnerController, this);
	
	Destroy();
}

