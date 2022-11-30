// Fill out your copyright notice in the Description page of Project Settings.


#include "AI1Controller.h"
#include "SplinePath.h"
#include "AI1.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AAI1Controller::AAI1Controller()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAI1Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	FindSplineActor();
	SetDuration();
	MoveToSplinePath();
}

//SplinePath 액터를 찾는다
void AAI1Controller::FindSplineActor()
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

//타임라인 재생속도 변수 설정
void AAI1Controller::SetDuration_Implementation()
{
	UCharacterMovementComponent* CharacterMovementComponent = Cast<AAI1>(GetOwner())->GetCharacterMovement();
	USplineComponent* SplineComponent = SplineReference->GetSplineComponent();

	if(CharacterMovementComponent != nullptr && SplineComponent != nullptr)
		Duration = (SplineComponent->GetSplineLength()) / (CharacterMovementComponent->MaxWalkSpeed);
}