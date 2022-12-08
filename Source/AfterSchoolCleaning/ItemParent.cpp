#include "ItemParent.h"

AItemParent::AItemParent()
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

void AItemParent::BeginPlay()
{
	Super::BeginPlay();
}

void AItemParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemParent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->ActorHasTag("Player"))
			UseItem();
	}
}

void AItemParent::UseItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("ItemParent::UseItem"));
	Destroy();
}
