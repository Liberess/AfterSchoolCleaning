// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolSubsystem.h"

bool UObjectPoolSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}

void UObjectPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	InstantiateObjects(100);
}

void UObjectPoolSubsystem::Deinitialize()
{

}

void UObjectPoolSubsystem::InstantiateObjects(int32 size)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> Obstacle(TEXT("Blueprint'/Game/Weapon/Ammo.Ammo'"));
	if (Obstacle.Succeeded())
	{
		if (Obstacle.Object)
		{
			ObsBlueprint = (UClass*)Obstacle.Object->GeneratedClass;
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

			AActor* temp = world->SpawnActor<AActor>(ObsBlueprint, SpawnLocation, rotator, SpawnParams);

			if (temp != nullptr)
			{
				temp->SetActorHiddenInGame(true);
				Objects.Add(temp);
			}
		}
	}
}

AActor* UObjectPoolSubsystem::SpawnObject(FVector spawnLocation, FRotator rotation)
{
	AActor* temp;

	if (Objects.Num() > 0)
	{
		temp = Objects.Pop();

		temp->SetActorLocation(spawnLocation);
		temp->SetActorRotation(rotation);
	}
	else
	{
		FActorSpawnParameters SpawnParams;
		temp = GetWorld()->SpawnActor<AActor>(ObsBlueprint, spawnLocation, rotation, SpawnParams);
	}

	temp->SetActorHiddenInGame(false);

	return temp;
}

void UObjectPoolSubsystem::ReturnObject(AActor* obj)
{
	obj->SetActorLocation(FVector::ZeroVector);
	obj->SetActorRotation(FRotator::ZeroRotator);
	obj->SetActorHiddenInGame(true);
	Objects.Add(obj);
}