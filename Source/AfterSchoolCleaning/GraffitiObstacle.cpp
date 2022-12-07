// Fill out your copyright notice in the Description page of Project Settings.


#include "GraffitiObstacle.h"
#include "ObjectPoolSubsystem.h"

// Sets default values
AGraffitiObstacle::AGraffitiObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (mesh != nullptr)
	{
		RootComponent = mesh;
	}

	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	if (collision != nullptr)
	{
		collision->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void AGraffitiObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGraffitiObstacle::WipeObstacle(int count)
{
	deleteCount =- count;

	if (deleteCount <= 0)
	{
		DeleteObstacle();
	}
}

void AGraffitiObstacle::DeleteObstacle()
{
	UObjectPoolSubsystem* ObjectPool = GetWorld()->GetSubsystem<UObjectPoolSubsystem>();
	ObjectPool->ReturnObject(Type, this);
}
