// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pawns/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Misc/HelperFunctions.h"
#include "../Actor/ConsumableObject.h"
#include "../LatentActions/UpdateSizeLatentAction.h"

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
	previousVelocity = GetVelocity();
	isGrounded = GetCharacterMovement()->IsMovingOnGround();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look", this, &APlayerCharacter::LookUpAt);
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
		AddMovementInput(GetActorForwardVector(), val);
		float rot = val * rotationSpeed * GetWorld()->GetDeltaSeconds();
		DEBUGMESSAGE("Rot: %f", rot)
		GetMesh()->AddRelativeRotation(FQuat(0, rot, 0, 1));
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
		float rot = -val * rotationSpeed * GetWorld()->GetDeltaSeconds();
		GetMesh()->AddRelativeRotation(FQuat(rot, 0, 0, 1));
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * turnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAt(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * lookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::InitalizeComponents()
{
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	springArmComponent->SetupAttachment(RootComponent);
	springArmComponent->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComponent->SetupAttachment(springArmComponent, USpringArmComponent::SocketName);
	cameraComponent->bUsePawnControlRotation = false; // Rotate the arm based on the controller
}

void APlayerCharacter::OnObjectEatten(float val)
{
	size = val;
	UpdateColliderSize(val);
	UpdateSpeed(size);
	UpdateMeshSize(size);
	UpdateCameraBoom(val);
}

void APlayerCharacter::UpdateMeshSize(float val)
{
	float s = size * sizeToScaleRatio;
	GetMesh()->SetRelativeScale3D(FVector(s, s, s));
	
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

void APlayerCharacter::CalculateBounce(AConsumableObject* consumableObject, const FVector normal)
{
	//Add force to repel player
	FVector n = normal;
	n.Normalize();
	FVector v = previousVelocity;
	v.Normalize();
	FVector u = FVector::DotProduct(v, n) * n;
	u.Normalize();
	FVector w = v - u;
	v = w - u;
	if (isGrounded)
	{
		LaunchCharacter(v * consumableObject->launchFactor * groundedLaunchRatio, true, true);
	}
	else
	{
		LaunchCharacter(v * consumableObject->launchFactor, true, true);
	}
}

void APlayerCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto potentialConsumableObject = Cast<AConsumableObject>(OtherActor);
	if (potentialConsumableObject)
	{
		if (size < potentialConsumableObject->currentSize)
		{
			CalculateBounce(potentialConsumableObject, Hit.ImpactNormal);
			GetWorld()->GetLatentActionManager().AddNewAction(this, 1, new UpdatePlayerSizeLatentAction(1, this,
				GetWorld()->GetDeltaSeconds(), 1.0f,size *  potentialConsumableObject->sizeDecreaseRatio * -1));
		}
		else
		{
			//Start eat/grow functionality
			GetWorld()->GetLatentActionManager().AddNewAction(this, 1, new UpdatePlayerSizeLatentAction(1, this, 
				GetWorld()->GetDeltaSeconds(), 1.0f, potentialConsumableObject->sizeChangeOnConsumed));
			if (!OtherActor->IsPendingKill())
				OtherActor->Destroy();
			//Start destruction or destory object
		}
	}
}