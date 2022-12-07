// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GraffitiObstacle.generated.h"

UENUM(BlueprintType)
enum class EObstacleType : uint8
{
	EWallObs = 0	UMETA(DisplayName = "Obstacle Wall"),
	EFloorObs		UMETA(DisplayName = "Obstacle Floor"),
};

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

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* collision;

	UPROPERTY(EditAnywhere, Category = "Graffiti Obstacle", meta = (AllowPrivateAccess = "true"))
	EObstacleType Type;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Graffiti Obstacle", meta = (AllowPrivateAccess = "true"))
	int32 deleteCount;

	int32 curDeleteCount;

	bool active;

	void Init();

	void Deactivate();

public:	
	void SetActive(bool InActive);

	FORCEINLINE bool GetActive() { return active; }

	UFUNCTION(BlueprintCallable, Category = "Graffiti Obstacle")
	void WipeObstacle(EObstacleType _type, int count);
};
