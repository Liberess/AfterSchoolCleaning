// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolSubsystem.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EObstacleType : uint8
{
	E_Wall = 0	UMETA(DisplayName = "Wall Obstacle"),
	E_Floor		UMETA(DisplayName = "Floor Obstacle"),
};


UCLASS()
class AFTERSCHOOLCLEANING_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<class AActor> WallObsBlueprint;

	UPROPERTY()
	TSubclassOf<class AActor> FloorObsBlueprint;

	TArray<AActor*> WallObjects;

	TArray<AActor*> FloorObjects;

	void InstantiateObjects(int32 size);

public: 
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION()
	AActor* SpawnObject(EObstacleType obstacle, FVector spawnLocation, FRotator rotation);

	UFUNCTION()
	void ReturnObject(EObstacleType obstacle, AActor* obj);
};
