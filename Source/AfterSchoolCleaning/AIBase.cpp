// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBase.h"
#include "AIControllerBase.h"

// Sets default values
AAIBase::AAIBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ObjectPooler = CreateDefaultSubobject<UObjectPool>(TEXT("ObjectPooler"));

	IsGrounded = true;
	IsInteractable = true;

	Tags.Add(TEXT("AI"));
}

// Called when the game starts or when spawned
void AAIBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIBase::IsOnSleep_Implementation()
{
	IsInteractable = false;
	Cast<AAIControllerBase>(GetController())->StopAI();

	if (IsValid(CurrentPlacedItemArea))
		CurrentPlacedItemArea->OnDrawDebugBox(FColor::Yellow);
}

void AAIBase::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, 
						bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, 
						const FHitResult& Hit)
{
	if (!IsInteractable)
		return;

	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (IsValid(Other))
	{
		if (Other->ActorHasTag("Ground"))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, TEXT("Ground"));
			IsGrounded = true;

			if (IsValid(CurrentPlacedItemArea))
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, TEXT("IsValid"));
				if (CurrentPlacedItemArea->PlacedAreaTag == PlacedAreaTag)
				{
					GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, TEXT("Sleep"));
					IsOnSleep();
				}
			}
		}
	}
}