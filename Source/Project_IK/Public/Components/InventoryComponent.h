/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 1.10.2025
Summary : Header file for the inventory Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "Structs/DPData.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UInventoryWidget;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
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

	UFUNCTION(BlueprintCallable)
	void PopUpInventory();

	UFUNCTION(BlueprintCallable)
	void RemoveInventory();

	TArray<FDPData> GetInventory();
	int GetInventorySize();

private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<FDPData> inventory_;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	UInventoryWidget* inventory_widget_ref_;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TSubclassOf<UInventoryWidget> inventory_widget_class_;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int inventory_size_;
};