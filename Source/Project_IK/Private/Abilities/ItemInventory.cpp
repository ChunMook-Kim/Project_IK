/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.19.2024
Summary : Source file for Item inventory.
					It contains a technical data of items.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/ItemInventory.h"
#include "Managers/ItemDataManager.h"
#include "Abilities/Item.h"

void UItemInventory::AddItem(TWeakObjectPtr<UItem> item)
{
	if (item_inventory_.Num() < 3)
	{
		if (item.IsValid())
		{
			item_inventory_.Add(item.Get());
		}
	}
}

void UItemInventory::AddItem(FItemData item_data)
{

	if (item_inventory_.Num() < 3)
	{
		UItem* item = NewObject<UItem>(this, item_class_);
		item->InitializeItemUsingData(item_data);

		item_inventory_.Add(item);
	}

}

TWeakObjectPtr<UItem> UItemInventory::GetItem(int32 index)
{
	if (item_inventory_.IsValidIndex(index))
	{
		return item_inventory_[index];
	}

	return nullptr;
}

void UItemInventory::RemoveItem(int32 index)
{
	if (item_inventory_.IsValidIndex(index))
	{
		item_inventory_.RemoveAt(index);
	}
}
