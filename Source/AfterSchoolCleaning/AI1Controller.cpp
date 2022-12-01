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

void AAI1Controller::BeginPlay()
{
	Super::BeginPlay();

}

void AAI1Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, TEXT("OnPossess"));

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

void AAI1Controller::ProcessMovementTimeline(float value)
{
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
void AAI1Controller::MoveToSplinePath_Implementation()
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

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, MovementTimeline.IsPlaying()? TEXT("true") : TEXT("false"));
}