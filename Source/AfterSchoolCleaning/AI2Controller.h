// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI2Controller.generated.h"

/**
 * 
 */
UCLASS()
class AFTERSCHOOLCLEANING_API AAI2Controller : public AAIController
{
	GENERATED_BODY()

public:
	AAI2Controller();
	virtual void OnPossess(APawn* InPawn) override;

	void RunAI();
	void StopAI();

	static const FName Key_NextPos;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
