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
}

void AAIControllerBase::StopAI()
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
