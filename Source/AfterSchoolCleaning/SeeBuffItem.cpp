#include "SeeBuffItem.h"

#include "AfterSchoolCleaningGameModeBase.h"
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
	
	if (SeeDuration <= 0.0f)
		SeeDuration = 20.0f;
}

void ASeeBuffItem::UseItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("SeeBuffItem::UseItem"));

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	AAfterSchoolCleaningGameModeBase* MyGameMode = Cast<AAfterSchoolCleaningGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if(IsValid(MyGameMode))
		MyGameMode->SetOutlinePostProcess(true, SeeDuration);
}