#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Sweeper.generated.h"

UENUM(BlueprintType)
enum class ETool : uint8
{
	Hand UMETA(DisplayName = "Hand"),
	Wall UMETA(DisplayName = "Wall"),
	Floor UMETA(DisplayName = "Floor")
};

USTRUCT(BlueprintType)
struct FToolStat
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ToolName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxUseToolCount;
};

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
	
	void SetEnabledUseTool();

	float LastJumpTime;
	float LastUseToolTime;

	bool CanJump;
	bool CanUseTool;

	FVector MoveDirection;

	FTimerHandle JumpTimer;
	FTimerHandle UseToolTimer;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UseToolDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ETool CurrentTool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FToolStat> ToolStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int> CurrentUseToolCounts;

	UFUNCTION(BlueprintCallable)
	void ChangeTool(ETool Tool);

	UFUNCTION(BlueprintCallable)
	void UseTool();
};
