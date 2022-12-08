#pragma once

#include "CoreMinimal.h"
#include "Engine/PostProcessVolume.h"
#include "GameFramework/GameModeBase.h"
#include "AfterSchoolCleaningGameModeBase.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API AAfterSchoolCleaningGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	AAfterSchoolCleaningGameModeBase();

public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void SetOutlinePostProcess(bool Active, float Duration);

	FTimerHandle SeeOutlineTimer;

	APostProcessVolume* PostVolume;
};
