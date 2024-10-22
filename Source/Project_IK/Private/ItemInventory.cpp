/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.19.2024
Summary : Source file for Item inventory.
					It contains a technical data of items.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "ItemInventory.h"

#include "SkillBase.h"

// Usage:
// TSubclassOf<AItem> WeaponClass = AWeapon::StaticClass();

void UItemInventory::AddItem(TSubclassOf<USkillBase> item_class)
{
	if (*item_class)
	{
		item_inventory_.Add(NewObject<USkillBase>(this, item_class));
	}
}

USkillBase* UItemInventory::GetItem(int32 index)
{
	if (item_inventory_.IsValidIndex(index))
	{
		return item_inventory_[index].Get();
	}

	return nullptr;
}
