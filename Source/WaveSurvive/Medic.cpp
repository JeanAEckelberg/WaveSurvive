// Fill out your copyright notice in the Description page of Project Settings.


#include "Medic.h"
#include "Camera/CameraComponent.h"
// Sets default values
AMedic::AMedic()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	// Create a dummy root component to attach things to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// Attach our camera and visible object to the root component.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AMedic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMedic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		if (!CurrentVelocityF.IsZero() || !CurrentVelocityR.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocityF * DeltaTime) + (CurrentVelocityR * DeltaTime);
			SetActorLocation(NewLocation);
		}

		FRotator NewRotation = GetActorRotation();

		NewRotation.Yaw += CameraInput.X;

		NewRotation.Pitch += CameraInput.Y;

		SetActorRotation(NewRotation);
	}
}

// Called to bind functionality to input
void AMedic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveForward", this, &AMedic::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMedic::MoveRight);
	InputComponent->BindAxis("LookRight", this, &AMedic::LookRight);
	InputComponent->BindAxis("LookUp", this, &AMedic::LookUp);
	CameraInput = FVector2D(0.0f, 0.0f);
}

void AMedic::MoveForward(float AxisValue)
{
	// Move at 100 units per second forward or backward
	
		CurrentVelocityF = GetActorForwardVector() * FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMedic::MoveRight(float AxisValue)
{
	// Move at 100 units per second right or left
	CurrentVelocityR = GetActorRightVector() * FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMedic::LookRight(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void AMedic::LookUp(float AxisValue)
{
	CameraInput.Y = AxisValue;
}