// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SplinePath.h"
#include "Components/TimelineComponent.h"
#include "AI1Controller.generated.h"

/**
 * 
 */
UCLASS()
class AFTERSCHOOLCLEANING_API AAI1Controller : public AAIController
{
	GENERATED_BODY()

public:
	AAI1Controller();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(Category = "FollowSpline")
	void FindSplineActor();

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
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "FollowSpline")
	void SetDuration();

	UFUNCTION(BlueprintCallable, Category = "FollowSpline")
	void MoveToSplinePath();

	UFUNCTION()
	void ProcessMovementTimeline(float value);

	UFUNCTION()
	void OnEndMovementTimeline();

	UFUNCTION()
	void CreateObstacleObj();
};
