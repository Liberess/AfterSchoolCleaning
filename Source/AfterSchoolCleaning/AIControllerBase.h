// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class AFTERSCHOOLCLEANING_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase();

protected:
	float SpawnCooldown;

	FTimerHandle SpawnCooldownTimer;

public:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void RunAI();
	virtual void StopAI();

	virtual void MoveAI();
	virtual void StopMoveAI();
	virtual void CreateObstacleObj();

	UFUNCTION(BlueprintCallable)
	void PutOn();

	UFUNCTION(BlueprintCallable)
	void PutOut();

protected:
	virtual void SpawnGraffiti();

	virtual FHitResult RaycastToFindWall(FVector start, FVector end);
};
