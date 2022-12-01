#include "InteractableItemParent.h"

AInteractableItemParent::AInteractableItemParent()
{
	PrimaryActorTick.bCanEverTick = true;

	IsRotate = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> _ItemMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	if(_ItemMesh.Succeeded())
		ItemMesh->SetStaticMesh(_ItemMesh.Object);

	RootComponent = ItemMesh;
}

void AInteractableItemParent::BeginPlay()
{
	Super::BeginPlay();

	OriginVector = GetActorLocation();
}

void AInteractableItemParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentDistance = FVector::Distance(OriginVector, GetActorLocation());
	if(CurrentDistance >= MaxFarDistance)
		ResetLocation();
}

void AInteractableItemParent::SaveLocation()
{
	OriginVector = GetActorLocation();
}

void AInteractableItemParent::ResetLocation_Implementation()
{
	//SetActorLocation(OriginVector);
	//OriginVector = GetActorLocation();
}
