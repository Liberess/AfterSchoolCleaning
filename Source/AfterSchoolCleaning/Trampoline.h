#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Trampoline.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API ATrampoline : public AActor
{
	GENERATED_BODY()

public:
	ATrampoline();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TrampolineMesh;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Trampoline,
		meta=(ClampMin=0, ClampMax=2000, UIMin=0, UIMax=2000))
	float MaxVelocityZ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Trampoline,
		meta=(ClampMin=0, ClampMax=10, UIMin=0, UIMax=10))
	float MultipleAmount;

	UFUNCTION(BlueprintCallable)
	void TrampolineChracter(AActor* OtherActor);
};
