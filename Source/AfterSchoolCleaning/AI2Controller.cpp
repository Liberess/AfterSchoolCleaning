// Fill out your copyright notice in the Description page of Project Settings.


#include "AI2Controller.h"
#include "AI2.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Kismet/GameplayStatics.h"


const FName AAI2Controller::Key_NextPos(TEXT("NextPos"));

AAI2Controller::AAI2Controller()
{
	PrimaryActorTick.bCanEverTick = true;

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

	SpawnCooldown = Cast<AAI2>(InPawn)->GetSpawnCooldown();

	RunAI();
	CreateObstacleObj();
}

void AAI2Controller::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		RunBehaviorTree(BTAsset);
	}
}

void AAI2Controller::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr == BehaviorTreeComponent) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}

void AAI2Controller::CreateObstacleObj()
{
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AAI2Controller::SpawnGraffity, SpawnCooldown, true);
}

void AAI2Controller::SpawnGraffity()
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	AGraffitiObstacle* PoolableActor = Cast<AAI2>(GetPawn())->GetObjectPooler()->GetPooledObject();
	if (PoolableActor == nullptr)
	{
		return;
	}

	FHitResult wallPos = RaycastToFindWall();
	if (wallPos.Actor == NULL)
	{
		return;
	}

	FVector newPos = wallPos.ImpactPoint + PoolableActor->GetActorUpVector() * 0.1f;

	PoolableActor->SetActorLocation(newPos);

	PoolableActor->SetActive(true);
}

FHitResult AAI2Controller::RaycastToFindWall()
{
	FHitResult hitResult;
	FVector startLocation = GetPawn()->GetActorLocation();
	FVector endLocation = GetPawn()->GetActorLocation() + GetPawn()->GetActorUpVector() * -150;

	bool isHitResult = GetWorld()->LineTraceSingleByObjectType(
		hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_WorldStatic);

	return hitResult;
}