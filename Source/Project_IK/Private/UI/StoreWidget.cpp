/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.15.2025
Summary : Source file for main Widget in StoreLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/StoreWidget.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/ItemDataManager.h"
#include "Managers/DronePluginManager.h"

#include "Blueprint/WidgetTree.h"
#include "UI/StoreSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Button.h"

void UStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!game_instance)
	{
		return;
	}
	const UItemDataManager* item_data_manager = game_instance->GetItemDataManager();
	const UDronePluginManager* drone_plugin_manager = game_instance->GetDronePluginManager();

	// Need to initialize widgets
	items_ = item_data_manager->GetUniqueItemDataRandomly(STOCK);
	dps_ = drone_plugin_manager->GetUniqueDPDataRandomly(STOCK);

	if (store_widget_class_)
	{
		for (int32 i = 0; i < STOCK; i++)
		{
			UStoreSlot* slot = WidgetTree->ConstructWidget<UStoreSlot>(store_widget_class_);
			slot->SetTexture(items_[i]->item_icon_);
			slot->SetPrice(GetPriceByRarity(items_[i]->rarity_));
			UHorizontalBoxSlot* box_slot = item_container_->AddChildToHorizontalBox(slot);
			if (box_slot)
			{
				box_slot->SetPadding(FMargin(120.f, 0.f));
			}
		}

		for (int32 i = 0; i < STOCK; i++)
		{
			UStoreSlot* slot = WidgetTree->ConstructWidget<UStoreSlot>(store_widget_class_);
			slot->SetTexture(dps_[i].dp_icon_);
			slot->SetPrice(GetPriceByRarity(dps_[i].rarity_));
			UHorizontalBoxSlot* box_slot = dp_container_->AddChildToHorizontalBox(slot);
			if (box_slot)
			{
				box_slot->SetPadding(FMargin(120.f, 0.f));
			}
		}
	}

	pay_button_->OnClicked.AddDynamic(this, &UStoreWidget::OnPayButtonClicked);
}

void UStoreWidget::NativeDestruct()
{
	Super::NativeDestruct();

	pay_button_->OnClicked.Clear();
}

void UStoreWidget::OnPayButtonClicked()
{
}

int32 UStoreWidget::GetPriceByRarity(ERarity rarity)
{
	switch (rarity)
	{
	case ERarity::S:
		return 100;
		break;
	case ERarity::A:
		return 75;
		break;
	case ERarity::B:
	default:
		return 50;
		break;
	}
}
