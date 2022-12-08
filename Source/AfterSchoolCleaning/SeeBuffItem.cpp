#include "SeeBuffItem.h"

ASeeBuffItem::ASeeBuffItem()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->InitSphereRadius(10.0f);
	SphereCollision->SetCollisionProfileName(TEXT("Trigger"));
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemParent::OnOverlapBegin);
	
	RootComponent = SphereCollision;
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> _ItemMesh(
		TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	if (_ItemMesh.Succeeded())
	{
		ItemMesh->SetStaticMesh(_ItemMesh.Object);
		ItemMesh->SetupAttachment(RootComponent);
	}
}

void ASeeBuffItem::BeginPlay()
{
	Super::BeginPlay();
}

void ASeeBuffItem::UseItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("SeeBuffItem::UseItem"));
}
