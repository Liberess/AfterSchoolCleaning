// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIBase.h"
#include "AI2.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API AAI2 : public AAIBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
