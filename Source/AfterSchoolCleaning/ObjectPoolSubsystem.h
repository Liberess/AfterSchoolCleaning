// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GraffitiObstacle.h"
#include "ObjectPoolSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class AFTERSCHOOLCLEANING_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	TArray<AGraffitiObstacle> Objects;

	void InstantiateObjects(int32 size);

public: 
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION()
	AActor* SpawnObject();

	UFUNCTION()
	void ReturnObject(AActor* obj);
};
