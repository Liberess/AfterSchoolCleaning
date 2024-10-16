// Fill out your copyright notice in the Description page of Project Settings.


#include "AI2.h"
#include "AI2Controller.h"

// Sets default values
AAI2::AAI2()
{
	static ConstructorHelpers::FClassFinder<AGraffitiObstacle> Obstacle(TEXT("/Game/BluePrints/GraffitiObstacle/BP_FloorGraffiti"));
	if (Obstacle.Succeeded())
	{
		ObjectPooler->PooledObjectSubclass = Obstacle.Class;
	}

	AIControllerClass = AAI2Controller::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AAI2::BeginPlay()
{
	Super::BeginPlay();
	
}
