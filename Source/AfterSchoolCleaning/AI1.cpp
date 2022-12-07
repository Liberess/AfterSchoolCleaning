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

	//AI Controller ¼³Á¤
	AIControllerClass = AAI1Controller::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AAI1::BeginPlay()
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void AAI1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

