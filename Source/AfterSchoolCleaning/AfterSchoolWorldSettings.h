#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "AfterSchoolWorldSettings.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API AAfterSchoolWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	AAfterSchoolWorldSettings();
	
	UPROPERTY(EditAnywhere, Category="AfterSchoolWorldSettings | Cleaning System")
	bool bUseCleaningManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta=(EditCondition="bUseCleaningManager==true", EditConditionHides, ClampMin=0, ClampMax=100, UIMin=0, UIMax=100, Units="percent"),
		Category="AfterSchoolWorldSettings | Cleaning System")
	float OrganizeRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta=(EditCondition="bUseCleaningManager==true", EditConditionHides, ClampMin=0, ClampMax=100,UIMin=0, UIMax=100, Units="percent"),
		Category="AfterSchoolWorldSettings | Cleaning System")
	float RemoveRatio;

	UPROPERTY(EditAnywhere, Category="AfterSchoolWorldSettings | Counting System")
	bool bUseCountManager;
};
