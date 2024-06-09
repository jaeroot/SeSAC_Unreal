// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeTrap.h"

#include "MazeCharacter.h"

AMazeTrap::AMazeTrap()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set Collision Box
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionProfileName(TEXT("Item"));
	BoxComponent->SetBoxExtent(FVector(100.0f, 100.0f, 200.0f));

	// Set Door Mesh (1 : Left, 2 : Right)
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxComponent);
	Mesh->SetCollisionProfileName(TEXT("Item"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Game/Maze/Trap/SM_MazeTrap.SM_MazeTrap"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	Mesh->SetRelativeScale3D(FVector(2.0f, 2.0f, 0.1f));
	Mesh->bHiddenInGame = true;
}

void AMazeTrap::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMazeTrap::CollisionBeginOverlapBox);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AMazeTrap::CollisionBeginOverlapMesh);
}

void AMazeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeTrap::CollisionBeginOverlapBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Character = Cast<AMazeCharacter>(OtherActor);
	if (Character != nullptr)
	{
		Mesh->SetSimulatePhysics(true);
	Mesh->bHiddenInGame = false;
	}
}

void AMazeTrap::CollisionBeginOverlapMesh(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Character = Cast<AMazeCharacter>(OtherActor);
	if (Character != nullptr)
	{
		if (!Character->GetShield())
		{
			Character->SetHP(-10);
		}
	}
}
