#include "CleaningManager.h"

#include "AfterSchoolWorldSettings.h"

bool UCleaningManager::ShouldCreateSubsystem(UObject* Outer) const
{
	if(!Super::ShouldCreateSubsystem(Outer))
		return false;

	UWorld* WorldOuter = Cast<UWorld>(Outer);
	if(IsValid(WorldOuter))
	{
		AAfterSchoolWorldSettings* WorldSettings = Cast<AAfterSchoolWorldSettings>(WorldOuter->GetWorldSettings());
		if(IsValid(WorldSettings))
			return WorldSettings->bUseCleaningManager;
	}
	
	return false;
}

void UCleaningManager::IncreasedProgress_Implementation(EProgressType ProgressType,float Progress)
{
	if(ProgressType == EProgressType::Organize)
	{
		
		OrganizeProgress += Progress;
	}
	else
	{
		RemoveProgress += Progress;

		//if(RemoveProgress)
	}
}

void UCleaningManager::DecreasedProgress_Implementation(EProgressType ProgressType,float Progress)
{
	if(ProgressType == EProgressType::Organize)
		OrganizeProgress -= Progress;
	else
		RemoveProgress -= Progress;
}
