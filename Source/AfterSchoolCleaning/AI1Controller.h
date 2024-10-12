// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIControllerBase.h"
#include "SplinePath.h"
#include "Components/TimelineComponent.h"
#include "AI1Controller.generated.h"

/**
 * 
 */
UCLASS()
class AFTERSCHOOLCLEANING_API AAI1Controller : public AAIControllerBase
{
	GENERATED_BODY()

public:
	AAI1Controller();

protected:
	UPROPERTY()
	TArray<ASplinePath*> SplinePaths;

	//Spline that AI1 will follow
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FollowSpline", meta = (AllowPrivateAccess = "true"))
	ASplinePath* SplineReference;

	//Timeline play speed
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FollowSpline", meta = (AllowPrivateAccess = "true"))
	float Duration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FollowSpline", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* MovementCurve;

	UPROPERTY()
	FTimeline MovementTimeline;

public:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	virtual void MoveAI() override;
	virtual void StopMoveAI() override;

	UFUNCTION()
	void ProcessMovementTimeline(float value);

	UFUNCTION()
	void OnEndMovementTimeline();

	UFUNCTION(Category = "FollowSpline")
	void FindSplineActor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "FollowSpline")
	void SetDuration();

	UFUNCTION(BlueprintCallable, Category = "FollowSpline")
	void MoveToSplinePath();

private:
	virtual void SpawnGraffiti() override;

	virtual FHitResult RaycastToFindWall() override;
};
