// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ObjectPool.h"
#include "AI1.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API AAI1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAI1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Spawner")
	UObjectPool* ObjectPooler;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnCooldown = 1.2f;

public:
	FORCEINLINE class UObjectPool* GetObjectPooler() { return ObjectPooler; }
	FORCEINLINE float GetSpawnCooldown() { return SpawnCooldown; }
};
