// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIControllerBase.h"
#include "AI2Controller.generated.h"

/**
 * 
 */
UCLASS()
class AFTERSCHOOLCLEANING_API AAI2Controller : public AAIControllerBase
{
	GENERATED_BODY()

public:
	AAI2Controller();

	static const FName Key_NextPos;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;

public:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void MoveAI() override;
	virtual void StopMoveAI() override;

private:
	virtual void SpawnGraffiti() override;

	virtual FHitResult RaycastToFindWall() override;
};
