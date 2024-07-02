#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/DamageEvents.h"
#include "DataStructure/LinkedList.h"

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