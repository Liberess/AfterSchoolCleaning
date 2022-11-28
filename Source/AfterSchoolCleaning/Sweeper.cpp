#include "Sweeper.h"
#include "Camera/CameraActor.h"
#include "GameFramework/PawnMovementComponent.h"

ASweeper::ASweeper()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASweeper::BeginPlay()
{
	Super::BeginPlay();

	if (MoveSpeed <= 0)
		MoveSpeed = 1;

	if (MinTimeBetweenJump <= 0.0f)
		MinTimeBetweenJump = 1.0f;

	CanJump = true;
}

void ASweeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if(MoveDirection.IsZero())
	{
		const FVector NewLocation = GetActorLocation() + (MoveDirection * DeltaTime * MoveSpeed);
		SetActorLocation(NewLocation);
	}*/
}

void ASweeper::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASweeper::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASweeper::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ASweeper::Jump);
}

void ASweeper::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue * MoveSpeed);
	//MoveDirection.X = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}

void ASweeper::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue * MoveSpeed);
	//MoveDirection.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}

void ASweeper::Jump()
{
	if (!CanJump)
		return;

	ACharacter::Jump();

	CanJump = false;
	GetWorldTimerManager().SetTimer(JumpTimer, this, &ASweeper::CheckJumpState, MinTimeBetweenJump, false);
}

void ASweeper::CheckJumpState()
{
	if (GetMovementComponent()->IsFalling())
	{
		GetWorldTimerManager().SetTimer(JumpTimer, this, &ASweeper::CheckJumpState, 0.1f, false);
	}
	else
	{
		GetWorldTimerManager().SetTimer(JumpTimer, this, &ASweeper::SetEnabledJump, MinTimeBetweenJump, false);
	}
}

void ASweeper::SetEnabledJump()
{
	CanJump = true;
	GetWorldTimerManager().ClearTimer(JumpTimer);

	GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Cyan, TEXT("NOW, CAN JUMP!"));
}
