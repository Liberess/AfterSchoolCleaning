#pragma once

#include "CoreMinimal.h"
#include "ItemParent.h"
#include "WallToolBuffItem.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API AWallToolBuffItem : public AItemParent
{
	GENERATED_BODY()

public:
	AWallToolBuffItem();
	
	virtual void BeginPlay() override;
	
	virtual void UseItem() override;
};
