// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraffitiObstacle.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API AGraffitiObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGraffitiObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Graffiti Obstacle", meta = (AllowPrivateAccess = "true"))
	int32 deleteCount;

public:	
	UFUNCTION(BlueprintCallable, Category = "Graffiti Obstacle")
	void WipeObstacle(int count);

	UFUNCTION(BlueprintCallable, Category = "Graffiti Obstacle")
	void DeleteObstacle();
};
