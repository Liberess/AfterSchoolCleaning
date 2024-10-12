// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"
#include "AIBase.h"

AAIControllerBase::AAIControllerBase()
{

}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SpawnCooldown = Cast<AAIBase>(InPawn)->GetSpawnCooldown();

	RunAI();
}

void AAIControllerBase::RunAI()
{
	MoveAI();
	CreateObstacleObj();
	GetPawn()->SetActorRotation(FRotator().ZeroRotator);
}

void AAIControllerBase::StopAI()
{
	StopMoveAI();
	GetWorldTimerManager().ClearTimer(SpawnCooldownTimer);
}

void AAIControllerBase::MoveAI()
{
}

void AAIControllerBase::StopMoveAI()
{
}

void AAIControllerBase::CreateObstacleObj()
{
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AAIControllerBase::SpawnGraffiti, SpawnCooldown, true);
}

void AAIControllerBase::PutOn()
{
	StopAI();
}

void AAIControllerBase::PutOut()
{
	RunAI();
}

void AAIControllerBase::SpawnGraffiti()
{

}

FHitResult AAIControllerBase::RaycastToFindWall()
{
	return FHitResult();
}
