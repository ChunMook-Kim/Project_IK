/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 1.10.2025
Summary : Source file for the Inventory Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/InventoryWidget.h"

#include "Characters/HeroBase.h"
#include "Components/CharacterStatComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/WrapBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DronePluginManager.h"
#include "UI/DPSlot.h"
#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKGameModeBase.h"
void UInventoryWidget::Initialize(UInventoryComponent* inventory_component)
{
	inventory_component_ref_ = inventory_component;
	heroDP_generic_->slot_type_ = EDPSlotType::HeroGeneral;
	heroDP_periodic_->slot_type_ = EDPSlotType::HeroPeriodic;
	scroll_box_->AddChild(wrap_box_);
}

void UInventoryWidget::LoadInventoryComponent()
{
	AIKGameModeBase* ik_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if(ik_mode->GetHeroContainers().IsEmpty() == false)
	{
		if (auto selected_hero = Cast<AHeroBase>(ik_mode->GetHeroContainers()[cur_hero_idx_]))
		{
			auto char_stat_cache = selected_hero->GetCharacterStat();
			EDPType g_dp = char_stat_cache->GetGeneralDP();
			EDPType p_dp = char_stat_cache->GetPeriodicDP();
			const UDronePluginManager* game_instance = Cast<UIKGameInstance>(GetGameInstance())->GetDronePluginManager();
		
			heroDP_generic_->dp_data_ = game_instance->GetDPData(g_dp);
			heroDP_periodic_->dp_data_ = game_instance->GetDPData(p_dp);
		}
	}
	wrap_box_->ClearChildren();
	inventory_slots_.Reset();
	inventory_slots_.Init(nullptr, inventory_component_ref_->GetInventorySize());
	auto inventory_data = inventory_component_ref_->GetInventory();
	for(int i = 0; i < inventory_data.Num(); i++)
	{
		inventory_slots_[i] = Cast<UDPSlot>(CreateWidget(GetWorld(), slot_BP_class_));
		inventory_slots_[i]->dp_data_ = inventory_data[i];
		inventory_slots_[i]->grid_idx_ = i;
		inventory_slots_[i]->SetImageTexture();
		wrap_box_->AddChild(inventory_slots_[i]);
	}
}

void UInventoryWidget::ApplyHeroDP()
{
	AIKGameModeBase* ik_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (auto selected_hero = Cast<AHeroBase>(ik_mode->GetHeroContainers()[cur_hero_idx_]))
	{
		auto char_stat_cache = selected_hero->GetCharacterStat();
		char_stat_cache->SetGeneralDP(heroDP_generic_->dp_data_.dp_type_);
		char_stat_cache->SetPeriodicDP(heroDP_periodic_->dp_data_.dp_type_);
	}
}