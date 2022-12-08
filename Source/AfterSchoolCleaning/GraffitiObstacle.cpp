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

	Tags.Add(TEXT("Interactable"));

	SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void AGraffitiObstacle::BeginPlay()
{
	Super::BeginPlay();

	Init();
	SetActive(true);
}


void AGraffitiObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGraffitiObstacle::SetActive(bool InActive)
{
	active = InActive;
	SetActorHiddenInGame(!InActive);
}

void AGraffitiObstacle::Deactivate()
{
	Init();
	SetActive(false);
}

void AGraffitiObstacle::Init()
{
	curDeleteCount = deleteCount;
	IsInteractable = true;
	mesh->SetCollisionProfileName("InteractableActor");
	SetActorLocation(FVector().ZeroVector);
	SetActorRotation(FRotator().ZeroRotator);
}

void AGraffitiObstacle::WipeObstacle(ETool type, int count)
{
	if (type != Type)
		return;

	curDeleteCount =- count;

	if (curDeleteCount <= 0)
	{
		CompleteWipe();
	}
}

void AGraffitiObstacle::CompleteWipe_Implementation()
{
	IsInteractable = false;

	Deactivate();
}
