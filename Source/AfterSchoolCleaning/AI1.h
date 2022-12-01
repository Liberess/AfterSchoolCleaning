// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SplinePath.h"
#include "AI1.generated.h"

UCLASS()
class AFTERSCHOOLCLEANING_API AAI1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAI1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
