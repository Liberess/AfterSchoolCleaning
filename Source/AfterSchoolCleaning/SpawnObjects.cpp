// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnObjects.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
ASpawnObjects::ASpawnObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;

	ObjectPooler = CreateDefaultSubobject<UObjectPool>(TEXT("ObjectPooler"));
}

// Called when the game starts or when spawned
void ASpawnObjects::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ASpawnObjects::Spawn, SpawnCooldown, false);
}

void ASpawnObjects::Spawn()
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	AGraffitiObstacle* PoolableActor = ObjectPooler->GetPooledObject();
	if (PoolableActor == nullptr)
	{
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ASpawnObjects::Spawn, SpawnCooldown, false);
		return;
	}

	PoolableActor->SetActorLocation(myCharacter->GetNavAgentLocation());
	PoolableActor->SetActorRotation(myCharacter->GetActorRotation());
	PoolableActor->SetActive(true);

	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ASpawnObjects::Spawn, SpawnCooldown, false);
}

