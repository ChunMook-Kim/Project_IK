/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 1.10.2025
Summary : Source file for the inventory Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Components/InventoryComponent.h"
#include "WorldSettings/IKGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
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
	inventory_.Init(FDPData(), inventory_size_);
	inventory_widget_ref_ = Cast<UInventoryWidget>(CreateWidget(GetWorld(), inventory_widget_class_));
	inventory_widget_ref_->Initialize(this);
	inventory_widget_ref_->LoadInventoryComponent();

	AddDP(EDPType::FireRange);
	AddDP(EDPType::FireRateBurst);
	AddDP(EDPType::LaserBeam);

	RemoveDP(2);
}

TArray<FDPData>& UInventoryComponent::GetInventory()
{
	return inventory_;
}

int UInventoryComponent::GetInventorySize()
{
	return inventory_size_;
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
	inventory_[index] = FDPData();
}

void UInventoryComponent::PopUpInventory()
{
	inventory_widget_ref_->LoadInventoryComponent();
	inventory_widget_ref_->AddToViewport();
	auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->bShowMouseCursor = true;
}

void UInventoryComponent::RemoveInventory()
{
	inventory_widget_ref_->RemoveFromParent();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
	inventory_widget_ref_->ApplyHeroDP();
	inventory_widget_ref_->ApplyInventoryComponent();
}