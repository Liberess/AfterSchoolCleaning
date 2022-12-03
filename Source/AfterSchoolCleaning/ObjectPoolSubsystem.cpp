// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolSubsystem.h"

bool UObjectPoolSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}

void UObjectPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UObjectPoolSubsystem::Deinitialize()
{

}


void UObjectPoolSubsystem::InstantiateObjects(int32 size)
{
	for (int i = 0; i < size; i++)
	{
		Objects.Emplace(GetWorld()->SpawnActor(AGraffitiObstacle::StaticClass()));
	}
}


AActor* UObjectPoolSubsystem::SpawnObject()
{
	AActor* temp;

	return temp;
}

void UObjectPoolSubsystem::ReturnObject(AActor* obj)
{

}