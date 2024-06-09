// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TimelineComponent.h"
#include "SeSAC/GameInfo.h"
#include "GameFramework/Actor.h"
#include "MazeDoor.generated.h"

UCLASS()
class SESAC_API AMazeDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMazeDoor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	// 업데이트 트랙 이벤트를 처리할 Float 트랙 시그니처
	FOnTimelineFloat UpdateFunctionFloat;

	// 타임라인 그래프에 따라 문의 상대적 위치를 업데이트하는 함수
	UFUNCTION()
	void UpdateTimelineComponent(float Output);

public:
	UPROPERTY(EditAnywhere, Category = "Door")
	bool DoorLocked = false;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UArrowComponent> ArrowComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> DoorMesh1;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> DoorMesh2;

	// DoorMesh를 업데이트하는 Timeline Component
	UPROPERTY()
	TObjectPtr<UTimelineComponent> DoorTimelineComponent;
	// 커브 에셋 보관 변수
	UPROPERTY()
	TObjectPtr<UCurveFloat> DoorCurve;
	
	bool bIsFront;
};
