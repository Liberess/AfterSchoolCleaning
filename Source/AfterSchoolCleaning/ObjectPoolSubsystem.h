// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolSubsystem.generated.h"

/**
 * 
 */

UCLASS()
class AFTERSCHOOLCLEANING_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> ObsBlueprint;

	TArray<AActor*> Objects;

	void InstantiateObjects(int32 size);

public: 
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION()
	AActor* SpawnObject(FVector spawnLocation, FRotator rotation);

	UFUNCTION()
	void ReturnObject(AActor* obj);
};
