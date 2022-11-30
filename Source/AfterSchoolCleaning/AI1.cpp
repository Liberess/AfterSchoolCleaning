// Fill out your copyright notice in the Description page of Project Settings.


#include "AI1.h"
#include "AI1Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAI1::AAI1()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//AI Controller ¼³Á¤
	//AIControllerClass = AAI1Controller::StaticClass();
	//AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AAI1::BeginPlay()
{
	Super::BeginPlay();

	FindSplineActor();
}

// Called every frame
void AAI1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAI1::FindSplineActor()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASplinePath::StaticClass(), actors);

	for (AActor* actor : actors)
	{
		ASplinePath* Spline = Cast<ASplinePath>(actor);

		if (Spline != nullptr)
			SplinePaths.Add(Spline);
	}

	SplineReference = SplinePaths[0];
}

// Called to bind functionality to input
void AAI1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

