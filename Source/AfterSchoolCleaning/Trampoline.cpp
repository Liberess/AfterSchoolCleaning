#include "Trampoline.h"
#include "GameFramework/Character.h"

ATrampoline::ATrampoline()
{
	PrimaryActorTick.bCanEverTick = true;

	TrampolineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrampolineMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> _TrampolineMesh(
		TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	if (_TrampolineMesh.Succeeded())
	{
		TrampolineMesh->SetStaticMesh(_TrampolineMesh.Object);
		RootComponent = TrampolineMesh;
	}

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(TrampolineMesh);
}

void ATrampoline::BeginPlay()
{
	Super::BeginPlay();

	if (MultipleAmount <= 0.0f)
		MultipleAmount = 1.2f;

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATrampoline::OnOverlapBegin);
}

void ATrampoline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrampoline::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
		TrampolineChracter(OtherActor);
}

void ATrampoline::TrampolineChracter(AActor* OtherActor)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (IsValid(Character))
	{
		FVector Vector = Character->GetVelocity();
		Vector.Z = (Vector.Z * -MultipleAmount >= MaxVelocityZ) ? MaxVelocityZ : Vector.Z * -MultipleAmount;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Z 1 = %f"), Vector.Z));
		if(Vector.Z == 0.0f)
		{
			Vector.X *= 0.2f; 
			Vector.Y *= 0.2f; 
			Vector.Z = 300.0f;
		}
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Z 2 = %f"), Vector.Z));
		Character->LaunchCharacter(Vector, true, true);
	}
}
