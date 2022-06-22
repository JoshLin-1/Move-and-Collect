// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallitemBase.h"

#include "PracticeUE5/RollaBallGameModeBase.h"
#include "PracticeUE5/RollablePawn.h"

// Sets default values
ARollaBallitemBase::ARollaBallitemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create Components
	Mesh= CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	RootComponent = Mesh;

	//bind one function to another in the engine
	//Ex: bind my own function to oncomponentbeginoverlap event
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARollaBallitemBase::OverlapBegin);
	

}

// Called when the game starts or when spawned
void ARollaBallitemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARollaBallitemBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<ARollablePawn>(OtherActor)!= nullptr)
	{
		Collected();
	}
}

void ARollaBallitemBase::Collected_Implementation()
{
	//TODO-Do Game Mode Stuff
	//we can add TODO
	ARollaBallGameModeBase* GameMode = Cast<ARollaBallGameModeBase>(GetWorld()->GetAuthGameMode());

	if(GameMode)
	{
		GameMode->ItemCollected();
	}
	
}



