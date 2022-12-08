// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ObjectPool.h"
#include "PlacedAIArea.h"
#include "PlacedItemArea.h"
#include "AIBase.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API AAIBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBase();

public:
	UPROPERTY(BlueprintReadWrite)
	bool IsInteractable;

	UPROPERTY(BlueprintReadWrite)
	bool IsGrounded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlacedAreaTag PlacedAreaTag;

	APlacedAIArea* CurrentPlacedItemArea;

protected:
	UPROPERTY(EditAnywhere, Category = "Spawner")
	UObjectPool* ObjectPooler;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnCooldown = 1.2f;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IsOnSleep();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

public:	
	FORCEINLINE class UObjectPool* GetObjectPooler() { return ObjectPooler; }
	FORCEINLINE float GetSpawnCooldown() { return SpawnCooldown; }
};
