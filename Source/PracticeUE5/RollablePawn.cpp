// Fill out your copyright notice in the Description page of Project Settings.


#include "RollablePawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ARollablePawn::ARollablePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create Components - Before this step they won't exist on our Actor, they've only been defined.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	//Set the Root Component to be our Mesh.
	RootComponent=Mesh;
	//Attach the SpringArm to the Mesh, Spring will now follow the Mesh transform.
	SpringArm->SetupAttachment(Mesh);
	//Attach the Camera to the SpringArm, Camera will now follow the SpringArm transform.
	Camera->SetupAttachment(SpringArm);

	//Set physics to true
	Mesh->SetSimulatePhysics(true);

	//Set default SpringArm inherited false
	SpringArm->bInheritPitch= false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Mesh->OnComponentHit.AddDynamic(this, &ARollablePawn::OnHit);

}

// Called when the game starts or when spawned
void ARollablePawn::BeginPlay()
{
	Super::BeginPlay();

	//Account for mass in MoveForce
	MoveForce = MoveForce* Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
	
	
	
}

// Called every frame
// void ARollablePawn::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// }

void ARollablePawn::MoveRight(float Value)
{
	//Get The Right Vector of the camera as it doesn't rotate and move the player in this direction based on the input and MoveForce
	const FVector Right = Camera->GetRightVector()*MoveForce*Value;
	Mesh->AddForce(Right);
}

void ARollablePawn::MoveForward(float Value)
{
	const FVector Forward = Camera->GetForwardVector()*MoveForce*Value;
	Mesh->AddForce(Forward);
}

void ARollablePawn::Jump()
{
	//Cap the number of jumps we can make.
	if (JumpCount>=MaxJumpCount){return;}
	
	//Apply an impulse to the Mesh in the Z Axis.
	Mesh->AddImpulse(FVector(0,0,JumpImpulse));

	//Track how many times we've jumped.
	JumpCount++;
}

void ARollablePawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	//Get Direction we hit the surface on the Z axis.
	//Const: 不能修改的常數
	const float HitDirection = Hit.Normal.Z;

	//Check
	// GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Cyan, FString::Printf(TEXT("Z Normal: %f"), HitDirection));
	// UE_LOG()
	
	//If it's more than 0 then we've hit something below us. 1 is flat, anything between is a slope.
	if (HitDirection>0)
	{
		JumpCount= 0;
	}
}



// Called to bind functionality to input
void ARollablePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Custom Input Axis Bindings.
	InputComponent->BindAxis("MoveForward", this, &ARollablePawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARollablePawn::MoveRight);

	//Custom Action Binding.
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollablePawn::Jump);
}

