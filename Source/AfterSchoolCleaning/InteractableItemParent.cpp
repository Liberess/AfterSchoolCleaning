#include "InteractableItemParent.h"

AInteractableItemParent::AInteractableItemParent()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> _ItemMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	if(_ItemMesh.Succeeded())
		ItemMesh->SetStaticMesh(_ItemMesh.Object);

	RootComponent = ItemMesh;
}

void AInteractableItemParent::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractableItemParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
