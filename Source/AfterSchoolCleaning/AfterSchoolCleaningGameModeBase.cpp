#include "AfterSchoolCleaningGameModeBase.h"

#include "Kismet/GameplayStatics.h"

AAfterSchoolCleaningGameModeBase::AAfterSchoolCleaningGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/Blueprints/BP_Sweeper"));

	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AAfterSchoolCleaningGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	AActor* Actor = UGameplayStatics::GetActorOfClass(this, APostProcessVolume::StaticClass());
	if (IsValid(Actor))
		PostVolume = Cast<APostProcessVolume>(Actor);
}

void AAfterSchoolCleaningGameModeBase::SetOutlinePostProcess(bool Active, float Duration)
{
	if(!IsValid(PostVolume))
		return;

	GetWorldTimerManager().ClearTimer(SeeOutlineTimer);
	
	if(Active)
	{
		PostVolume->bEnabled = true;
		GetWorld()->GetTimerManager().SetTimer(SeeOutlineTimer, FTimerDelegate::CreateLambda([&]()
		{
			PostVolume->bEnabled = false;
		}), Duration, false);
	}
	else
	{
		PostVolume->bEnabled = false;
	}
}
