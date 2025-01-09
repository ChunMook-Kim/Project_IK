// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
class UInventoryComponent;
UCLASS()
class PROJECT_IK_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitInventoryWidget(UInventoryComponent* inventory_component);
	void LoadInventoryComponent();
	void ApplyHeroDP();
private:
	UInventoryComponent* inventory_component_ref_;
};
