// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ObstacleAIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class AFTERSCHOOLCLEANING_API AObstacleAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AObstacleAIControllerBase();

protected:
	virtual void BeginPlay() override;
};
