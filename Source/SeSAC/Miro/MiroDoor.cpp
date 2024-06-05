// Fill out your copyright notice in the Description page of Project Settings.


#include "MiroDoor.h"

AMiroDoor::AMiroDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	SetRootComponent(mBody);
	mBody->SetCollisionProfileName(TEXT("Item"));
	mBody->SetBoxExtent(FVector(300.0f, 200.0f, 150.0f));

	mMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	mMesh1->SetupAttachment(mBody);
	mMesh1->SetCollisionProfileName(TEXT("BlockAll"));

	mMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	mMesh2->SetupAttachment(mBody);
	mMesh2->SetCollisionProfileName(TEXT("BlockAll"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Game/Miro/Cube.Cube"));
	if (MeshAsset.Succeeded())
	{
		mMesh1->SetStaticMesh(MeshAsset.Object);
		mMesh2->SetStaticMesh(MeshAsset.Object);
	}
	mMesh1->SetRelativeLocation(FVector(0.0f, 200.0f, 0.0f));
	mMesh1->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	mMesh1->SetRelativeScale3D(FVector(0.1f, 2.0f, 3.0f));
	
	mMesh2->SetRelativeLocation(FVector(0.0f, -200.0f, 0.0f));
	mMesh2->SetRelativeScale3D(FVector(0.1f, 2.0f, 3.0f));
}

void AMiroDoor::BeginPlay()
{
	Super::BeginPlay();

	mBody->OnComponentBeginOverlap.AddDynamic(this, &AMiroDoor::CollisionBeginOverlap);
	mBody->OnComponentEndOverlap.AddDynamic(this, &AMiroDoor::CollisionEndOverlap);
}

void AMiroDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMiroDoor::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Character = Cast<ACharacter>(OtherActor);
	if (Character != nullptr)
	{
		auto result = FVector::DotProduct(GetActorForwardVector(), Character->GetActorForwardVector());
		if (result >= 0)
		{
			bIsFront = true;
		}
		else
		{
			bIsFront = false;
		}
		OpenDoor();
	}
}

void AMiroDoor::CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Character = Cast<ACharacter>(OtherActor);
	if (Character != nullptr)
	{
		CloseDoor();
	}
}

void AMiroDoor::CloseDoor_Implementation()
{
}

void AMiroDoor::OpenDoor_Implementation()
{
}

