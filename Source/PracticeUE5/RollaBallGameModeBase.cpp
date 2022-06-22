// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallGameModeBase.h"
#include "RollaBallWidget.h"
#include "Blueprint/UserWidget.h"
#include "Items/RollaBallitemBase.h"
#include "Kismet/GameplayStatics.h"


void ARollaBallGameModeBase::BeginPlay()
{
	/*Create Array of Items which will be collected and put into a list of information
	 *TArray: Typed Array. make it have return Actor*/
	TArray<AActor*> Items;

	//GetWorld: current world, which is specific type will add to items list
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollaBallitemBase::StaticClass(), Items);

	//Return integer value 
	ItemInLevel = Items.Num();

	if(GameWidgetClass)
	{
		// set gamewidget to be the result of cast to the uRollaballwidget, against the funciton return of the create widget
		// if the widgetclass is rollaballwidget, gamewidget will fill with value, otherwise it won't has value
		
		GameWidget = Cast<URollaBallWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if (GameWidget != nullptr)//if it has value
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
		
	}

	
}

void ARollaBallGameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemInLevel);
}

void ARollaBallGameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}
