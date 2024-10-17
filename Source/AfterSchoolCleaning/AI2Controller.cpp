// Fill out your copyright notice in the Description page of Project Settings.


#include "AI2Controller.h"
#include "AI2.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Kismet/GameplayStatics.h"


const FName AAI2Controller::Key_NextPos(TEXT("NextPos"));

AAI2Controller::AAI2Controller()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/BluePrints/BP_AI/AI2/BB_AI2"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/BluePrints/BP_AI/AI2/BT_AI2"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AAI2Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SpawnCooldown = Cast<AAIBase>(InPawn)->GetSpawnCooldown();

	RunAI();
}

void AAI2Controller::MoveAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		RunBehaviorTree(BTAsset);
	}
}

void AAI2Controller::StopMoveAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr == BehaviorTreeComponent) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}

void AAI2Controller::SpawnGraffiti()
{
	if (!Cast<AAIBase>(GetPawn())->active)
		return;

	AGraffitiObstacle* PoolableActor = Cast<AAIBase>(GetPawn())->GetObjectPooler()->GetPooledObject();
	if (PoolableActor == nullptr)
	{
		return;
	}

	FVector startLocation = GetPawn()->GetActorLocation();
	FVector endLocation = GetPawn()->GetActorLocation() + GetPawn()->GetActorUpVector() * -150;

	FHitResult wallPos = RaycastToFindWall(startLocation, endLocation);
	if (wallPos.Actor == NULL)
	{
		return;
	}

	FVector newPos = wallPos.ImpactPoint + PoolableActor->GetActorUpVector() * 0.2f;
	PoolableActor->SetGraffitiObstacle(newPos);
}