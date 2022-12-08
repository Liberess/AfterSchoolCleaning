// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraffitiObstacle.h"
#include "ObjectPool.h"
#include "SpawnObjects.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API ASpawnObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnObjects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	UObjectPool* ObjectPooler;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	bool trigger;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnCooldown = 1.2f;

	FTimerHandle SpawnCooldownTimer;

	void Spawn(); 
};
