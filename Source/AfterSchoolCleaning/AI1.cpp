// Fill out your copyright notice in the Description page of Project Settings.


#include "AI1.h"
#include "AI1Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAI1::AAI1()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ObjectPooler = CreateDefaultSubobject<UObjectPool>(TEXT("ObjectPooler"));

	static ConstructorHelpers::FClassFinder<AGraffitiObstacle> Obstacle(TEXT("/Game/BluePrints/GraffitiObstacle/BP_WallGraffiti"));
	if (Obstacle.Succeeded())
	{
		ObjectPooler->PooledObjectSubclass = Obstacle.Class;
	}

	//AI Controller ¼³Á¤
	AIControllerClass = AAI1Controller::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AAI1::BeginPlay()
{
	Super::BeginPlay();

}