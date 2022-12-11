// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBase.h"
#include "AIControllerBase.h"
#include "GameFramework/Actor.h"

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
	
	SpawnPoint = GetActorLocation();
}

void AAIBase::OnSleep_Implementation()
{
	IsInteractable = false;
	Cast<AAIControllerBase>(GetController())->StopAI();

	GetWorld()->GetTimerManager().SetTimer(SleepTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		WakeUp();
	}), SleepTime, false);
}

void AAIBase::WakeUp_Implementation()
{
	SpawnAI();

	IsInteractable = true;
	Cast<AAIControllerBase>(GetController())->RunAI();
}

void AAIBase::SpawnAI()
{
	SetActorLocation(SpawnPoint);
}

void AAIBase::SetActive(bool value)
{
	active = value;
	SetActorHiddenInGame(!value);
	SetActorEnableCollision(value);
	SetActorTickEnabled(value);
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
		}
	}
}