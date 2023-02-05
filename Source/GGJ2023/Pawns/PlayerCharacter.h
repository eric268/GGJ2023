// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class AConsumableObject;
class APlayerHUD;
class APC;
class UDialogueWidget;
class GameDialogue;

UCLASS()
class GGJ2023_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Components
	UPROPERTY(EditAnywhere, Category = "Components")
		USpringArmComponent* springArmComponent;
	UPROPERTY(EditAnywhere, Category = "Components")
		UCameraComponent* cameraComponent;

	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float maxSize = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float size = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float turnRate = 25.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float lookUpRate = 25.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float minimumSizeDecreaseValue = 5.0f;

	//Attribute Ratios
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Ratios")
		float sizeToScaleRatio = 0.02f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Ratios")
		float speedToSizeRatio = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Ratios")
		float cameraBoomToSizeRatio = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute Ratios")
		float groundedLaunchRatio = 5.0f;

	//Camera Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Attributes")
		float minPitch = -90.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Attributes")
		float maxPitch = 0.0f;

	//Animation Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float rotationSpeed = 1.0f;

	APlayerHUD* playerHUD;
	void OnObjectEatten(float val);
private:
	void UpdateRecentlyLostSize();
	FTimerHandle recentlyLostSizeHandle;
	bool recentlyLostSize = false;
	GameDialogue* loadedDialogue;
	UDialogueWidget* dialogueWidget;
	APC* playerController;

	FVector previousVelocity;
	bool isGrounded = true;
	int latentActionID = 0;

	void InitalizePlayer();
	void Jump();
	void MoveForward(float val);
	void MoveRight(float val);
	void TurnAtRate(float Rate);
	void LookUpAt(float val);
	void InitalizeComponents();

	void UpdateCameraBoom(float val);
	void UpdateSpeed(float val);
	void UpdateColliderSize(float val);
	void UpdateMeshSize(float val);
	void CalculateBounce(AConsumableObject* consumableObject, const FVector normal);
	void OnCollision(AConsumableObject* consumableObject, const FVector normal);

	UFUNCTION(BlueprintCallable)
		void DisplayDialogue(FString text);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
