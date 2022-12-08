#pragma once

#include "CoreMinimal.h"
#include "ItemParent.h"
#include "Engine/PostProcessVolume.h"
#include "SeeBuffItem.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API ASeeBuffItem : public AItemParent
{
	GENERATED_BODY()

public:
	ASeeBuffItem();
	
	virtual void BeginPlay() override;
	
	virtual void UseItem() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SeeDuration;
};
