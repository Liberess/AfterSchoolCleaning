// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "SplinePath.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API ASplinePath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplinePath();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline", meta = (AllowPrivateAccess = "true"))
	class USplineComponent* SplineComponent;

public:	
	FORCEINLINE class USplineComponent* GetSplineComponent() const { return SplineComponent; }
};
