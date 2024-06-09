// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeDoor.h"

#include "MazeCharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/TimelineComponent.h"

AMazeDoor::AMazeDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set Collision Box
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionProfileName(TEXT("Item"));
	BoxComponent->SetBoxExtent(FVector(300.0f, 200.0f, 150.0f));

	// Set Arrow Component (to check Forward)
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(BoxComponent);

	// Set Door Mesh (1 : Left, 2 : Right)
	DoorMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh1"));
	DoorMesh1->SetupAttachment(BoxComponent);
	DoorMesh1->SetCollisionProfileName(TEXT("BlockAll"));

	DoorMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh2"));
	DoorMesh2->SetupAttachment(BoxComponent);
	DoorMesh2->SetCollisionProfileName(TEXT("BlockAll"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Game/Maze/Door/SM_Door.SM_Door"));
	if (MeshAsset.Succeeded())
	{
		DoorMesh1->SetStaticMesh(MeshAsset.Object);
		DoorMesh2->SetStaticMesh(MeshAsset.Object);
	}
	DoorMesh1->SetRelativeLocation(FVector(0.0f, 200.0f, 0.0f));
	DoorMesh1->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	DoorMesh1->SetRelativeScale3D(FVector(0.1f, 2.0f, 3.0f));
	
	DoorMesh2->SetRelativeLocation(FVector(0.0f, -200.0f, 0.0f));
	DoorMesh2->SetRelativeScale3D(FVector(0.1f, 2.0f, 3.0f));

	// Set Timeline
	DoorTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComponent"));
	UpdateFunctionFloat.BindDynamic(this, &AMazeDoor::UpdateTimelineComponent);
	
	DoorCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("DoorCurve"));
	static ConstructorHelpers::FObjectFinder<UCurveFloat>
	DoorCurveFloat(TEXT("/Game/Maze/Door/CF_Door.CF_Door"));
	if (DoorCurveFloat.Succeeded())
	{
		DoorCurve = DoorCurveFloat.Object;
		DoorTimelineComponent->AddInterpFloat(DoorCurve, UpdateFunctionFloat);
	}
	DoorTimelineComponent->SetLooping(false);
}

void AMazeDoor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMazeDoor::CollisionBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AMazeDoor::CollisionEndOverlap);
}

void AMazeDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeDoor::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Character = Cast<AMazeCharacter>(OtherActor);
	if (Character != nullptr)
	{
		if (DoorLocked)
		{
			if (Character->GetItemCount() < 5)
			{
				return;
			}
			else
			{
				DoorLocked = false;
			}
		}
		
		auto result = FVector::DotProduct(GetActorForwardVector(), Character->GetActorLocation() - GetActorLocation());
		if (result >= 0)
		{
			bIsFront = true;
		}
		else
		{
			bIsFront = false;
		}
		
		DoorTimelineComponent->PlayFromStart();
	}
}

void AMazeDoor::CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Character = Cast<AMazeCharacter>(OtherActor);
	if (Character != nullptr)
	{
		if (DoorLocked)
		{
			return;
		}
		
		DoorTimelineComponent->ReverseFromEnd();
	}
}

void AMazeDoor::UpdateTimelineComponent(float Output)
{
	// 타임라인 커브의 출력을 바탕으로 문의 새 상대적 위치 설정 및 구성
	FRotator DoorNewRotation1 = FRotator(0.0f, 180.0f, 0.0f);
	FRotator DoorNewRotation2 = FRotator(0.0f, 0.0f, 0.0f);

	if (bIsFront)
	{
		DoorNewRotation1.Yaw -= Output;
		DoorNewRotation2.Yaw += Output;
	}
	else
	{
		DoorNewRotation1.Yaw += Output;
		DoorNewRotation2.Yaw -= Output;
	}
	
	DoorMesh1->SetRelativeRotation(DoorNewRotation1);
	DoorMesh2->SetRelativeRotation(DoorNewRotation2);
}
