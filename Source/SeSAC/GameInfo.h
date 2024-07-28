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

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	Main,
	Sub
};

UENUM(BlueprintType)
enum class EQuestClearType : uint8
{
	Monster,
	Item
};

USTRUCT(BlueprintType)
struct FQuestClearData
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EQuestClearType Type;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ClearName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ClearCount;
};

USTRUCT(BlueprintType)
struct FQuestInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EQuestType QuestType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Content;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FQuestClearData> ClearArray;
};

USTRUCT(BlueprintType)
struct FQuestClearUseData
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EQuestClearType Type;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ClearName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ClearCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ClearCountMax;
};

USTRUCT(BlueprintType)
struct FQuestInfoData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool QuestEnable = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EQuestType QuestType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Content;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FQuestClearUseData> ClearArray;
};