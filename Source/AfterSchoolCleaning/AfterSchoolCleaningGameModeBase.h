#pragma once

#include "CoreMinimal.h"
#include "Engine/PostProcessVolume.h"
#include "GameFramework/GameModeBase.h"
#include "GraffitiObstacle.h"
#include "AfterSchoolCleaningGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EObstacleType : uint8
{
	WallObs = 0	UMETA(DisplayName = "Obstacle Wall"),
	FloorObs	UMETA(DisplayName = "Obstacle Floor"),
};

DECLARE_MULTICAST_DELEGATE(FWallDebuffDel);
DECLARE_MULTICAST_DELEGATE(FFloorDebuffDel);

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

	UFUNCTION(BlueprintCallable)
	void SetObstacleDebuff(EObstacleType ObsType, bool Active, float Duration);

	FTimerHandle WallDebuffTimer;
	FTimerHandle FloorDebuffTimer;
	FTimerHandle SeeOutlineTimer;

	APostProcessVolume* PostVolume;

	FWallDebuffDel Fuc_WallDebuff;
	FFloorDebuffDel Fuc_FloorDebuff;

	ASweeper* Sweeper;
};
