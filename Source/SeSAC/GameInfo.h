#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/DamageEvents.h"
#include "DataStructure/LinkedList.h"

#include "GameInfo.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(SeSAC, Warning, All);

UENUM(BlueprintType)
enum class EPlayerJob : uint8
{
	None,
	Knight,
	Archer,
	Magician,
	Gunner
};

USTRUCT(BlueprintType)
struct FPlayerInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPlayerJob Job;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mAttack;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mDefense;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mHP;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mMP;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mMoveSpeed;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mAttackDistance;	
};