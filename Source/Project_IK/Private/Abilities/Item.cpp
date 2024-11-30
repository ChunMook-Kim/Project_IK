/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.27.2024
Summary : Source file for Item class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/Item.h"

#include "Managers/ItemDataManager.h"
#include "Components/TargetingComponent.h"

#include "Components/CharacterStatComponent.h"

void UItem::InitializeItemUsingData(FItemData item_data)
{
	item_data_ = item_data;
}

void UItem::UseItem(const FTargetData& TargetData)
{
	switch (item_data_.item_logic_)
	{
	case EItemLogicType::None:
		break;
	case EItemLogicType::RestoreHP:
		RestoreHP(TargetData.target_actors_[0]);
		break;
	default:
		break;
	}
}

FItemData UItem::GetData() const
{
	return item_data_;
}

void UItem::RestoreHP(AActor* actor)
{
	if (!actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("UItem::RestoreHP -> Actor is invalid!!"));
		return;
	}
	UCharacterStatComponent* stat = actor->GetComponentByClass<UCharacterStatComponent>();
	if (stat)
	{
		// @@ TODO: Change fixed data into some variable.
		stat->SetHitPoint(stat->GetHitPoint() + 10.f);
		UE_LOG(LogTemp, Warning, TEXT("Use Item (RestoreHP) has been used successfully!"));
	}
}
