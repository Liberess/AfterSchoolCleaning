#include "AfterSchoolCleaningGameModeBase.h"

AAfterSchoolCleaningGameModeBase::AAfterSchoolCleaningGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/Blueprints/BP_Sweeper"));

	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}