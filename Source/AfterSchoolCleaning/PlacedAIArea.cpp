// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacedAIArea.h"
#include "DrawDebugHelpers.h"
#include "AIBase.h"
#include "Sweeper.h"

APlacedAIArea::APlacedAIArea()
{
	OnActorBeginOverlap.AddDynamic(this, &APlacedAIArea::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &APlacedAIArea::OnOverlapEnd);
}


void APlacedAIArea::BeginPlay()
{
	Super::BeginPlay();

	OnDrawDebugBox(FColor::Yellow);
}

void APlacedAIArea::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		AAIBase* AI = Cast<AAIBase>(OtherActor);
		if (IsValid(AI))
		{	
			bool isGrip = Cast<ASweeper>(GetWorld()->GetFirstPlayerController()->GetPawn())->IsGrip;

			if (!isGrip)
			{
				if (AI->PlacedAreaTag == this->PlacedAreaTag)
				{
					GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, TEXT("OnBed"));
					OnDrawDebugBox(FColor::Green);
					AI->OnSleep();
				}
				else
				{
					OnDrawDebugBox(FColor::Red);
					AI->SpawnAI();
				}
			}
		}
	}
}

void APlacedAIArea::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		AAIBase* AI = Cast<AAIBase>(OtherActor);
		if (IsValid(AI))
		{
			OnDrawDebugBox(FColor::Yellow);
		}
	}
}

void APlacedAIArea::OnDrawDebugBox(FColor DebugColor)
{
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), DebugColor, true, -1, 0, 1);
}
