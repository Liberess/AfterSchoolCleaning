#include "WallToolBuffItem.h"

AWallToolBuffItem::AWallToolBuffItem()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> _ItemMesh(
		TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	if (_ItemMesh.Succeeded())
		ItemMesh->SetStaticMesh(_ItemMesh.Object);

	RootComponent = ItemMesh;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->InitSphereRadius(0.5f);
	SphereCollision->SetCollisionProfileName(TEXT("Trigger"));
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemParent::OnOverlapBegin);
}

void AWallToolBuffItem::BeginPlay()
{
	Super::BeginPlay();
}

void AWallToolBuffItem::UseItem()
{
	Super::UseItem();

	
}
