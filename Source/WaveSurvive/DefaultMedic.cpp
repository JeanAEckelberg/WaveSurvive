// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultMedic.h"

// Sets default values
ADefaultMedic::ADefaultMedic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefaultMedic::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	
}

// Called every frame
void ADefaultMedic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultMedic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ADefaultMedic::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADefaultMedic::MoveRight);

	PlayerInputComponent->BindAxis("LookRight", this, &ADefaultMedic::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ADefaultMedic::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADefaultMedic::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ADefaultMedic::StopJump);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ADefaultMedic::Attack);
}

void ADefaultMedic::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ADefaultMedic::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ADefaultMedic::StartJump()
{
	bPressedJump = true;
}

void ADefaultMedic::StopJump()
{
	bPressedJump = false;
}

void ADefaultMedic::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("You are attacking"));
}