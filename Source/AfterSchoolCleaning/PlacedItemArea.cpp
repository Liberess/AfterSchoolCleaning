#include "PlacedItemArea.h"
#include "DrawDebugHelpers.h"
#include "InteractableItemParent.h"

#define print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Yellow, text)
#define printFString(duration, text, fstring) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Yellow, FString::Printf(Text(text), fstring))

APlacedItemArea::APlacedItemArea()
{
	OnActorBeginOverlap.AddDynamic(this, &APlacedItemArea::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &APlacedItemArea::OnOverlapEnd);
}

void APlacedItemArea::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Yellow, true, -1, 0, 1);
}

void APlacedItemArea::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		AInteractableItemParent* Item = Cast<AInteractableItemParent>(OtherActor);
		if (IsValid(Item))
		{
			Item->CurrentPlacedItemArea = this;

			if (Item->PlacedAreaTag == this->PlacedAreaTag)
				DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Green, true,
				             -1, 0, 1);
			else
				DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Red, true,
				 -1, 0, 1);
		}
	}
}

void APlacedItemArea::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		AInteractableItemParent* Item = Cast<AInteractableItemParent>(OtherActor);
		if (IsValid(Item))
		{
			Item->CurrentPlacedItemArea = nullptr;
			DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Yellow, true,
			             -1, 0, 1);
		}
	}
}
