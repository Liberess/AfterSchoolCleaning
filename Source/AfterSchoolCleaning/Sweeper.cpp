#include "Sweeper.h"
#include "Camera/CameraActor.h"
#include "GameFramework/PawnMovementComponent.h"

ASweeper::ASweeper()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}

void ASweeper::BeginPlay()
{
	Super::BeginPlay();

	if (MoveSpeed <= 0)
		MoveSpeed = 1;

	if (JumpDelay <= 0.0f)
		JumpDelay = 1.0f;

	if(UseToolDelay <= 0.0f)
		UseToolDelay = 1.0f;

	CurrentUseToolCounts.Empty();
	for(int i = 0; i < ToolStats.Num(); i++)
		CurrentUseToolCounts.Add(ToolStats[i].MaxUseToolCount);

	CanJump = true;
	CanUseTool = true;
}

void ASweeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASweeper::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASweeper::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASweeper::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ASweeper::Jump);
	PlayerInputComponent->BindAction(TEXT("Use"), EInputEvent::IE_Pressed, this, &ASweeper::UseTool);
	PlayerInputComponent->BindAction<TDelegate<void(ETool)>>(TEXT("Hand"), EInputEvent::IE_Pressed, this, &ASweeper::ChangeTool, ETool::Hand);
	PlayerInputComponent->BindAction<TDelegate<void(ETool)>>(TEXT("Wall"), EInputEvent::IE_Pressed, this, &ASweeper::ChangeTool, ETool::Wall);
	PlayerInputComponent->BindAction<TDelegate<void(ETool)>>(TEXT("Floor"), EInputEvent::IE_Pressed, this, &ASweeper::ChangeTool, ETool::Floor);
}

void ASweeper::MoveForward(float AxisValue)
{
	if(AxisValue != 0.0f)
		AddMovementInput(GetActorForwardVector(), AxisValue * MoveSpeed);
}

void ASweeper::MoveRight(float AxisValue)
{
	if(AxisValue != 0.0f)
		AddMovementInput(GetActorRightVector(), AxisValue * MoveSpeed);
}

void ASweeper::Jump()
{
	if (!CanJump)
		return;

	ACharacter::Jump();

	CanJump = false;
	GetWorldTimerManager().SetTimer(JumpTimer, this, &ASweeper::CheckJumpState, JumpDelay, false);
}

void ASweeper::CheckJumpState()
{
	if (GetMovementComponent()->IsFalling())
	{
		GetWorldTimerManager().SetTimer(JumpTimer, this, &ASweeper::CheckJumpState, 0.1f, false);
	}
	else
	{
		GetWorldTimerManager().SetTimer(JumpTimer, this, &ASweeper::SetEnabledJump, JumpDelay, false);
	}
}

void ASweeper::SetEnabledJump()
{
	CanJump = true;
	GetWorldTimerManager().ClearTimer(JumpTimer);

	GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Cyan, TEXT("Now, can jump!"));
}

void ASweeper::SetEnabledUseTool()
{
	CanUseTool = true;
	GetWorldTimerManager().ClearTimer(UseToolTimer);
}

void ASweeper::ChangeTool(ETool Tool)
{
	if(IsGrip)
		return;
	
	CurrentTool = Tool;
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::Printf(TEXT("%d"), (int)Tool));
}

void ASweeper::SetToolRemoveDamage(const ETool ToolType, const int NewDamage)
{
	//CurrentRemoveDamages[static_cast<int>(ToolType)] = NewDamage;
	ToolStats[static_cast<int>(ToolType)].RemoveDamage = NewDamage;
}

void ASweeper::PutObject_Implementation()
{
	
}

void ASweeper::UseTool_Implementation()
{
	if(!CanUseTool || CurrentUseToolCounts[static_cast<int>(CurrentTool)] <= 0)
		return;

	//CanJump
	CanUseTool = false;
	--CurrentUseToolCounts[static_cast<int>(CurrentTool)];
	GEngine->AddOnScreenDebugMessage(2, 2.0f, FColor::Yellow, TEXT("Use Tool"));

	GetWorldTimerManager().SetTimer(UseToolTimer, this, &ASweeper::SetEnabledUseTool, UseToolDelay, false);
}
