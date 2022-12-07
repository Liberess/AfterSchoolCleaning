// Fill out your copyright notice in the Description page of Project Settings.


#include "AI2.h"
#include "AI2Controller.h"

// Sets default values
AAI2::AAI2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAI2Controller::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AAI2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AAI2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

