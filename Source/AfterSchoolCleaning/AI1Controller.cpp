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

void AAI1Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementTimeline.IsPlaying())
	{
		MovementTimeline.TickTimeline(DeltaTime);
	}
}

void AAI1Controller::MoveAI()
{
	MovementTimeline.Play();
}

void AAI1Controller::StopMoveAI()
{
	MovementTimeline.Stop();
}

void AAI1Controller::ProcessMovementTimeline(float value)
{
	if (!IsValid(SplineReference))
		return;

	const float SplineLength = SplineReference->GetSplineComponent()->GetSplineLength();

	float distance = FMath::Lerp(0.0f, SplineLength, value);

	FVector CurrentSplineLocation = SplineReference->GetSplineComponent()->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
	MoveToLocation(CurrentSplineLocation);
}

void AAI1Controller::OnEndMovementTimeline()
{
	
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

	if(SplinePaths.Num() > 0)
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

//타임라인 실행
void AAI1Controller::MoveToSplinePath()
{
	FOnTimelineFloat ProgressFunction;
	ProgressFunction.BindUFunction(this, TEXT("ProcessMovementTimeline"));
	MovementTimeline.AddInterpFloat(MovementCurve, ProgressFunction);

	FOnTimelineEvent OnTimelineFinishedFunction;
	OnTimelineFinishedFunction.BindUFunction(this, TEXT("OnEndMovementTimeline"));
	MovementTimeline.SetTimelineFinishedFunc(OnTimelineFinishedFunction);

	MovementTimeline.SetTimelineLengthMode(TL_LastKeyFrame);
	MovementTimeline.SetLooping(true);
	MovementTimeline.SetPlayRate(1.0f / Duration);
	MovementTimeline.Play();
}

void AAI1Controller::SpawnGraffiti()
{
	if (!Cast<AAIBase>(GetPawn())->active)
		return;

	AGraffitiObstacle* PoolableActor = Cast<AAIBase>(GetPawn())->GetObjectPooler()->GetPooledObject();
	if (PoolableActor == nullptr)
	{
		return;
	}

	FVector startLocation = GetPawn()->GetActorLocation();
	FVector endLocation = GetPawn()->GetActorLocation() + GetPawn()->GetActorRightVector() * 150;

	FHitResult wallPos = RaycastToFindWall(startLocation, endLocation);
	if (wallPos.Actor == NULL)
	{
		return;
	}

	FRotator newRot = GetPawn()->GetActorUpVector().Rotation() * -1.0f + wallPos.ImpactNormal.Rotation();
	FVector newPos = wallPos.ImpactPoint + PoolableActor->GetActorUpVector() * 0.1f;
	PoolableActor->SetGraffitiObstacle(newPos, newRot);
}