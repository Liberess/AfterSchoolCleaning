#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CleaningManager.generated.h"

UENUM(BlueprintType)
enum class EProgressType : uint8
{
	Organize UMETA(DisplayName = "Organize"),
	Remove UMETA(DisplayName = "Remove")
};

UCLASS()
class AFTERSCHOOLCLEANING_API UCleaningManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(ClampMin = 0, ClampMax = 100))
	float TotalProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin=0, UIMax=100))
	float OrganizeProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RemoveProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxProgress;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IncreasedProgress(EProgressType ProgressType, float Progress);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DecreasedProgress(EProgressType ProgressType,float Progress);
};
