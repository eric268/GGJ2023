// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pawns/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Misc/HelperFunctions.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitalizeComponents();
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &APlayerCharacter::OnHit);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnObjectEatten(size + DeltaTime * 3);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::TurnAtRate);
}

void APlayerCharacter::Jump()
{
	if (GetMovementComponent()->IsMovingOnGround())
		ACharacter::Jump();
}
void APlayerCharacter::MoveForward(float val)
{
	if ((Controller != nullptr) && (val != 0.0f))
	{
		// find out which way is forward
		//const FRotator Rotation = Controller->GetControlRotation();
		//const FRotator YawRotation(0, Rotation.Yaw, 0);

		//// get forward vector
		//const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(GetActorForwardVector(), val);
	}
}
void APlayerCharacter::MoveRight(float val)
{
	if (val != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, val);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * turnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::InitalizeComponents()
{
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	springArmComponent->SetupAttachment(RootComponent);
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComponent->SetupAttachment(springArmComponent, USpringArmComponent::SocketName);
}

void APlayerCharacter::OnObjectEatten(float val)
{
	size = val;
	UpdateColliderSize(size);
	UpdateSpeed(size);
}

void APlayerCharacter::UpdateColliderSize(float val)
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(val);
	GetCapsuleComponent()->SetCapsuleRadius(val);
}

void APlayerCharacter::UpdateSpeed(float val)
{
	GetCharacterMovement()->MaxWalkSpeed = val * speedToSizeRatio;;
}

void APlayerCharacter::UpdateCameraBoom(float val)
{
	springArmComponent->TargetArmLength = val * cameraBoomToSizeRatio;
}

void APlayerCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	PRINT("HIT SOMETHING");
}