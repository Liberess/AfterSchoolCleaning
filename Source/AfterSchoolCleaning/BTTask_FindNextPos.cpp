// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNextPos.h"
#include "AI2Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindNextPos::UBTTask_FindNextPos()
{
	NodeName = TEXT("FindNextPos");
}

EBTNodeResult::Type UBTTask_FindNextPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation NextPos;
	FVector Origin(650.0f, 520.0f, 0.0f);
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, 500.0f, NextPos))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AAI2Controller::Key_NextPos, NextPos.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}