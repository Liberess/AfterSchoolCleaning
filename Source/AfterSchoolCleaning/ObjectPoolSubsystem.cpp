// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolSubsystem.h"

bool UObjectPoolSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);

	return true;
}

void UObjectPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	InstantiateObjects(100);
}

void UObjectPoolSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UObjectPoolSubsystem::InstantiateObjects(int32 size)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> WallObstacle(TEXT("/Game/BluePrints/GraffitiObstacle/BP_WallGraffiti.BP_WallGraffiti"));
	if (WallObstacle.Succeeded())
	{
		if (WallObstacle.Object)
		{
			WallObsBlueprint = (UClass*)WallObstacle.Object->GeneratedClass;
		}
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> FloorObstacle(TEXT("/Game/BluePrints/GraffitiObstacle/BP_FloorGraffiti"));
	if (FloorObstacle.Succeeded())
	{
		if (FloorObstacle.Object)
		{
			FloorObsBlueprint = (UClass*)FloorObstacle.Object->GeneratedClass;
		}
	}

	UWorld* world = GetWorld();
	if (world)
	{
		for (int i = 0; i < size; i++)
		{
			FActorSpawnParameters SpawnParams;
			FRotator rotator = FRotator::ZeroRotator;
			FVector SpawnLocation = FVector::ZeroVector;

			AActor* WallObs = world->SpawnActor<AActor>(WallObsBlueprint, SpawnLocation, rotator, SpawnParams);
			if (WallObs != nullptr)
			{
				WallObs->SetActorHiddenInGame(true);
				WallObjects.Add(WallObs);
			}

			AActor* FloorObs = world->SpawnActor<AActor>(FloorObsBlueprint, SpawnLocation, rotator, SpawnParams);
			if (FloorObs != nullptr)
			{
				FloorObs->SetActorHiddenInGame(true);
				FloorObjects.Add(WallObs);
			}
		}
	}
}

AActor* UObjectPoolSubsystem::SpawnObject(EObstacleType obstacle, FVector spawnLocation, FRotator rotation)
{
	AActor* temp;

	switch (obstacle)
	{
		case EObstacleType::E_Wall:
			if (WallObjects.Num() > 0)
			{
				temp = WallObjects.Pop();

				temp->SetActorLocation(spawnLocation);
				temp->SetActorRotation(rotation);
			}
			else
			{
				FActorSpawnParameters SpawnParams;
				temp = GetWorld()->SpawnActor<AActor>(WallObsBlueprint, spawnLocation, rotation, SpawnParams);
			}
			break;

		case EObstacleType::E_Floor:
			if (FloorObjects.Num() > 0)
			{
				temp = FloorObjects.Pop();

				temp->SetActorLocation(spawnLocation);
				temp->SetActorRotation(rotation);
			}
			else
			{
				FActorSpawnParameters SpawnParams;
				temp = GetWorld()->SpawnActor<AActor>(FloorObsBlueprint, spawnLocation, rotation, SpawnParams);
			}
			break;

		default:
			temp = nullptr;
			break;
	}

	temp->SetActorHiddenInGame(false);

	return temp;
}

void UObjectPoolSubsystem::ReturnObject(EObstacleType obstacle, AActor* obj)
{
	obj->SetActorLocation(FVector::ZeroVector);
	obj->SetActorRotation(FRotator::ZeroRotator);
	obj->SetActorHiddenInGame(true);

	switch (obstacle)
	{
		case EObstacleType::E_Wall:
			WallObjects.Add(obj);
			break;

		case EObstacleType::E_Floor:
			FloorObjects.Add(obj);
			break;
	}
}