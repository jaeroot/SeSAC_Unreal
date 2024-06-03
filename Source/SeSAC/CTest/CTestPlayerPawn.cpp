// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestPlayerPawn.h"

// #include "Camera/CameraComponent.h"

ACTestPlayerPawn::ACTestPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	/*
	UObject를 생성하는 방식
	CreateDefaultSubobject는 생성자에서만 사용할 수 있음, 생성자 말고 다른데서 쓰면 Error!
	CreateDefaultSubobject는 template 형식임
	접두어F - 데이터, 간단함 함수 등이 붙임
	FName - 언리얼 엔진에서 이름을 붙일 때 사용하는 타입
	언리얼은 unicode (w_char)을 사용하고 있음
	TEXT("")를 쓰면 wide char로 바꿔 줌
	CreateDefaultSubobject는 UObject를 상속받은 클래스를 생성해줄때 사용
	내부에서 객체를 생성하고 주소를 return해줌
	*/
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

#if WITH_EDITORONLY_DATA
	// editor에서만 mesh가 어디 있는지 표시해줌
	mMesh->bVisualizeComponent = true;
#endif
	
	SetRootComponent(mMesh);

	// Camera의 부모 Component로 Mesh를 지정함
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mMesh);
	mCamera->SetRelativeLocation(FVector{-500.0f, 0.0f, 90.0f});
	mCamera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
}

void ACTestPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

void ACTestPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTestPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

