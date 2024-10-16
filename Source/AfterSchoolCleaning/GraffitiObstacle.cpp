// Fill out your copyright notice in the Description page of Project Settings.


#include "GraffitiObstacle.h"

// Sets default values
AGraffitiObstacle::AGraffitiObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (mesh != nullptr)
	{
		RootComponent = mesh;
		mesh->SetCollisionProfileName("InteractableActor");
	}

	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	if (collision != nullptr)
	{
		collision->SetupAttachment(RootComponent);
		collision->SetCollisionProfileName("InteractableActor");
	}

	SetActive(true);

	curDeleteCount = 0;

	Tags.Add(TEXT("Interactable"));
}

// Called when the game starts or when spawned
void AGraffitiObstacle::BeginPlay()
{
	Super::BeginPlay();

	SetActive(true);
	curDeleteCount = 0;
}


void AGraffitiObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGraffitiObstacle::SetActive(bool InActive)
{
	active = InActive;
	collision->SetSimulatePhysics(InActive);
	SetActorHiddenInGame(!InActive);
	SetActorEnableCollision(InActive);
	SetActorTickEnabled(InActive);
}

void AGraffitiObstacle::Deactivate()
{
	Init();
	SetActive(false);
}

void AGraffitiObstacle::Init()
{
	curDeleteCount = 0;
	IsInteractable = true;
	SetActorLocation(FVector().ZeroVector);
	SetActorRotation(FRotator().ZeroRotator);
}

int32 AGraffitiObstacle::WipeObstacle(ETool type, int32 count)
{
	if (type != Type)
		return curDeleteCount;

	curDeleteCount = curDeleteCount + count;

	if (curDeleteCount >= deleteCount)
	{
		CompleteWipe();
	}

	return curDeleteCount;
}

void AGraffitiObstacle::SetGraffitiObstacle_Implementation(FVector pos, FRotator rot = FRotator().ZeroRotator)
{
	SetActorLocation(pos);
	SetActorRotation(rot);

	IsInteractable = true;

	SetActive(true);
}

void AGraffitiObstacle::CompleteWipe_Implementation()
{
	IsInteractable = false;

	Deactivate();
}
