// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeSAC/GameInfo.h"
#include "GameFramework/Actor.h"
#include "MazeItem.generated.h"

UCLASS()
class SESAC_API AMazeItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AMazeItem();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
};
