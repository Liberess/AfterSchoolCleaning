#include "SeeBuffItem.h"
#include "Kismet/GameplayStatics.h"

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
	
	AActor* Actor = UGameplayStatics::GetActorOfClass(this, APostProcessVolume::StaticClass());
	if(IsValid(Actor))
		PostVolume = Cast<APostProcessVolume>(Actor);

	if (SeeDuration <= 0.0f)
		SeeDuration = 10.0f;
}

void ASeeBuffItem::UseItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("SeeBuffItem::UseItem"));

	if (IsValid(PostVolume))
	{
		PostVolume->bEnabled = true;
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		GetWorldTimerManager().SetTimer(SeeTimer, this, &ASeeBuffItem::DisableOutline, SeeDuration, false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("No!!"));
	}
}

void ASeeBuffItem::DisableOutline()
{
	PostVolume->bEnabled = false;
	Destroy();
}
