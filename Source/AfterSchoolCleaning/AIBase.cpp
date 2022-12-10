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

void AAIBase::OnSleep_Implementation()
{
	IsInteractable = false;
	Cast<AAIControllerBase>(GetController())->StopAI();

	if (IsValid(CurrentPlacedItemArea))
		CurrentPlacedItemArea->OnDrawDebugBox(FColor::Yellow);

	GetWorld()->GetTimerManager().SetTimer(SleepTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		WakeUp();
	}), SleepTime, false); //반복도 여기서 추가 변수를 선언해 설정가능
}

void AAIBase::WakeUp_Implementation()
{
	IsInteractable = true;
	Cast<AAIControllerBase>(GetController())->RunAI();
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
			IsGrounded = true;

			if (IsValid(CurrentPlacedItemArea))
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, TEXT("IsValid"));
				if (CurrentPlacedItemArea->PlacedAreaTag == PlacedAreaTag)
				{
					GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, TEXT("Sleep"));
					OnSleep();
				}
			}
		}
	}
}