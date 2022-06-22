// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "RollablePawn.generated.h"

class UCameraComponent;
class USpringArmComponent;


UCLASS()
class PRACTICEUE5_API ARollablePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARollablePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Define Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* Mesh; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* Camera;

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveForce = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpImpulse = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxJumpCount = 1; 

	
public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	// Function
	void MoveRight(float Value);
	void MoveForward(float Value);
	void Jump();

	int32 JumpCount = 0;
	
	//Whenever you're creating a function with the intention to bind it, it needs to have some unreal boilerplate understanding of the macro system
	//EX: UFuUNCTION, told unreal engine to bind it with engine
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};