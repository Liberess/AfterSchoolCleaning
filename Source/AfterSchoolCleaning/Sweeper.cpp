#include "Sweeper.h"
#include "Camera/CameraActor.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"

ASweeper::ASweeper()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPPCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;

	CharacterSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	//CharacterSkeletalMesh->SetOnlyOwnerSee(true);
	CharacterSkeletalMesh->SetupAttachment(FirstPersonCameraComponent);
	CharacterSkeletalMesh->bCastDynamicShadow = false;
	CharacterSkeletalMesh->CastShadow = false;

	RayLocation = CreateDefaultSubobject<USceneComponent>(TEXT("RayLocation"));
	RayLocation->SetupAttachment(FirstPersonCameraComponent);
	//RayLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	ToolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ToolMesh"));
	ToolMesh->SetupAttachment(CharacterSkeletalMesh);
	ToolMesh->bCastDynamicShadow = false;
	ToolMesh->CastShadow = false;
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
	
	AnimInstance = CharacterSkeletalMesh->GetAnimInstance();
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
	ChangeToolMesh(Tool);
}

void ASweeper::SetToolRemoveDamage(const ETool ToolType, const int NewDamage)
{
	ToolStats[static_cast<int>(ToolType)].RemoveDamage = NewDamage;
}

void ASweeper::ChangeToolMesh(ETool ToolType)
{
	if(ToolType == ETool::Hand)
	{
		ToolMesh->SetStaticMesh(nullptr);
		return;
	}
	
	int ToolIndex = static_cast<int>(ToolType) - 1;
	ToolMesh->SetStaticMesh(ToolMeshs[ToolIndex]);
	const static FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, false);
	ToolMesh->AttachToComponent(CharacterSkeletalMesh, AttachRules, ToolSocketNames[ToolIndex]);
}

void ASweeper::PutObject_Implementation()
{
	
}

void ASweeper::UseTool_Implementation()
{
	int ToolIndex = static_cast<int>(CurrentTool);
	if(!CanUseTool || CurrentUseToolCounts[ToolIndex] <= 0)
		return;

	CanUseTool = false;
	--CurrentUseToolCounts[ToolIndex];
	GetWorldTimerManager().SetTimer(UseToolTimer, this, &ASweeper::SetEnabledUseTool, UseToolDelay, false);

	check(AnimInstance);

	if(CurrentTool != ETool::Hand && IsValid(ToolAnimations[ToolIndex-1]))
	{
		AnimInstance->Montage_Play(ToolAnimations[ToolIndex-1], 1.0f);
	}
}
