#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Sweeper.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API ASweeper : public ACharacter
{
	GENERATED_BODY()

public:
	ASweeper();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void Jump();
	void CheckJumpState();
	void SetEnabledJump();

	float LastJumpTime;

	bool CanJump;

	FVector MoveDirection;

	FTimerHandle JumpTimer;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinTimeBetweenJump;

	//void 
};
