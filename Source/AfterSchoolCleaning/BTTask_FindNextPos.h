// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindNextPos.generated.h"

/**
 * 
 */
UCLASS()
class AFTERSCHOOLCLEANING_API UBTTask_FindNextPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FindNextPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
