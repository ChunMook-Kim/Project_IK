// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/InventoryComponent.h"
#include "WorldSettings/IKGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "Managers/DronePluginManager.h"
#include "UI/InventoryWidget.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	inventory_size_ = 20;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	inventory_.Reserve(inventory_size_);
	inventory_widget_ref_ = Cast<UInventoryWidget>(CreateWidget(nullptr, inventory_widget_class_));
	//inventory_widget_class_->Init
}

int UInventoryComponent::GetEmptyIndex() const
{
	for (int i = 0; i < inventory_size_; ++i)
	{
		if (inventory_[i].dp_type_ == EDPType::Empty)
		{
			return i;
		}
	}
	return -1;
}


bool UInventoryComponent::AddDP(EDPType type)
{
	auto instance = GetWorld()->GetGameInstance();
	if (auto IK_instance = Cast<UIKGameInstance>(instance))
	{
		int index = GetEmptyIndex();
		if (index != -1)
		{
			inventory_[index] = IK_instance->GetDronePluginManager()->GetDPData(type);
			return true;
		}
	}
	return false;
}

void UInventoryComponent::RemoveDP(int index)
{
	inventory_[index] = FDronePluginData();
}
