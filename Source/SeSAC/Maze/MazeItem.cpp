// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeItem.h"

#include "MazeCharacter.h"

AMazeItem::AMazeItem()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set Collision Box
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionProfileName(TEXT("Item"));
	BoxComponent->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	// Set Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh1"));
	Mesh->SetupAttachment(BoxComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Game/Maze/Item/SM_MazeItem.SM_MazeItem"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}
}

void AMazeItem::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMazeItem::CollisionBeginOverlap);
}

void AMazeItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeItem::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Character = Cast<AMazeCharacter>(OtherActor);
	if (Character != nullptr)
	{
		Character->AddItemCount();
		Destroy();
	}
}

