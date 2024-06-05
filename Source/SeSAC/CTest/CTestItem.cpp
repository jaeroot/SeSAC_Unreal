// Fill out your copyright notice in the Description page of Project Settings.


#include "CTestItem.h"

#include "CTestGameMode.h"

ACTestItem::ACTestItem()
{
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	SetRootComponent(mBody);
	mBody->SetCollisionProfileName(TEXT("Item"));
	mBody->SetBoxExtent(FVector(128.0f, 128.0f, 128.0f));

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetupAttachment(mBody);
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Game/Test/TestMesh/Cube.Cube"));
	if (MeshAsset.Succeeded())
	{
		mMesh->SetStaticMesh(MeshAsset.Object);
	}
}

void ACTestItem::BeginPlay()
{
	Super::BeginPlay();

	mBody->OnComponentBeginOverlap.AddDynamic(this, &ACTestItem::CollisionBeginOverlap);
	mBody->OnComponentEndOverlap.AddDynamic(this, &ACTestItem::CollisionEndOverlap);
}

void ACTestItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTestItem::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(SeSAC, Warning, TEXT("Begin Overlap"));
	
	ACTestGameMode* GameMode = GetWorld()->GetAuthGameMode<ACTestGameMode>();
	if (GameMode)
	{
		GameMode->AddScore(10);
	}
	
	
	Destroy();
}

void ACTestItem::CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(SeSAC, Warning, TEXT("End Overlap"));
}

