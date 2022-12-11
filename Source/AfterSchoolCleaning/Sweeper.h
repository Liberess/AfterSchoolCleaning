#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Sweeper.generated.h"

UENUM(BlueprintType)
enum class ETool : uint8
{
	Hand UMETA(DisplayName = "Hand"),
	Wall UMETA(DisplayName = "Wall"),
	Floor UMETA(DisplayName = "Floor")
};

USTRUCT(BlueprintType, Blueprintable)
struct FToolStat
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ToolName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxUseToolCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RemoveDamage;
};

UCLASS()
class AFTERSCHOOLCLEANING_API ASweeper : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CharacterSkeletalMesh;
	
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

	bool CanJump;
	float LastJumpTime;
	float LastUseToolTime;

	FVector MoveDirection;

	FTimerHandle JumpTimer;
	FTimerHandle UseToolTimer;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float JumpDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interact)
	float UseToolDelay;
	
	UPROPERTY(BlueprintReadWrite, Category = Interact)
	bool CanUseTool;

	UPROPERTY(BlueprintReadWrite, Category = Interact)
	bool IsGrip;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interact)
	AActor* InteractObject;

	UPROPERTY(BlueprintReadWrite)
	FVector StartLocation;

	UPROPERTY(BlueprintReadWrite)
	FVector EndLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interact)
	ETool CurrentTool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interact)
	TArray<FToolStat> ToolStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interact)
	TArray<int> CurrentUseToolCounts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TArray<UAnimMontage*> ToolAnimation;

	UFUNCTION(BlueprintCallable)
	void ChangeTool(ETool Tool);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UseTool();

	UFUNCTION(BlueprintCallable)
	void SetToolRemoveDamage(const ETool ToolType, const int NewDamage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PutObject();
};
