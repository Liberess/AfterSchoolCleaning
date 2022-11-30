#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableItemParent.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API AInteractableItemParent : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractableItemParent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ItemMesh;
};
