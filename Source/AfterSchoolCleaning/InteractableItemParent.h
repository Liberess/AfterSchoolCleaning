#pragma once

#include "CoreMinimal.h"
#include "PlacedItemArea.h"
#include "Components/SphereComponent.h"
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

private:
	void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlacedAreaTag PlacedAreaTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsRotate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsInteractable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector OriginVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ResetTime;
	
	FTimerHandle ResetLocationTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsGrounded;

	APlacedItemArea* CurrentPlacedItemArea;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetLocation();

	UFUNCTION(BlueprintCallable)
	void CompleteOrganize();
};
