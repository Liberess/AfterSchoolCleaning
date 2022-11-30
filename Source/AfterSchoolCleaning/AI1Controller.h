// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleAIControllerBase.h"
#include "SplinePath.h"
#include "AI1Controller.generated.h"

/**
 * 
 */
UCLASS()
class AFTERSCHOOLCLEANING_API AAI1Controller : public AObstacleAIControllerBase
{
	GENERATED_BODY()

public:
	AAI1Controller();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	TArray<ASplinePath*> SplinePaths;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FollowSpline", meta = (AllowPrivateAccess = "true"))
	ASplinePath* SplineReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FollowSpline", meta = (AllowPrivateAccess = "true"))
	float Duration;

public:
	UFUNCTION(BlueprintCallable, Category = "FollowSpline")
	void FindSplineActor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "FollowSpline")
	void SetDuration();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "FollowSpline")
	void MoveToSplinePath();
};
