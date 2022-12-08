// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacedAIArea.h"
#include "DrawDebugHelpers.h"
#include "AIBase.h"

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
			AI->CurrentPlacedItemArea = this;

			if (AI->PlacedAreaTag == this->PlacedAreaTag)
				OnDrawDebugBox(FColor::Green);
			else
				OnDrawDebugBox(FColor::Red);
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
			AI->CurrentPlacedItemArea = nullptr;
			OnDrawDebugBox(FColor::Yellow);
		}
	}
}

void APlacedAIArea::OnDrawDebugBox(FColor DebugColor)
{
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), DebugColor, true, -1, 0, 1);
}
