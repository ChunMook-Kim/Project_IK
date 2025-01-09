// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Structs/DronePluginData.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UInventoryWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	int GetEmptyIndex() const;

public:
	bool AddDP(EDPType type);
	void RemoveDP(int index);

private:
	TArray<FDronePluginData> inventory_;
	UInventoryWidget* inventory_widget_ref_;
	TSubclassOf<UUserWidget> inventory_widget_class_;
	int inventory_size_;
};
