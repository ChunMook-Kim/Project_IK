// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSettings/IKGameInstance.h"

#include "Abilities/ItemInventory.h"
#include "UI/IKMaps.h"
#include "Abilities/MyTestItem.h"
#include "CharacterDataManager.h"
#include "LevelTransitionManager.h"

#include "Hero.h"
#include "EnemyGunner.h"

UIKGameInstance::UIKGameInstance()
	:Super::UGameInstance()
{
}

void UIKGameInstance::Init()
{
	Super::Init();

	InitializeCharacterDataManager();
	InitializeItemInventory();
	InitializeMaps();
	InitializeLevelTransitionManager();

	item_inventory_->AddItem(UMyTestItem::StaticClass());
}

const UCharacterDataManager* UIKGameInstance::GetCharacterDataManager() noexcept
{
	return character_data_manager_;
}

UItemInventory* UIKGameInstance::GetItemInventory() const noexcept
{
	return item_inventory_;
}

const UIKMaps* UIKGameInstance::GetMapPtr() const noexcept
{
	return maps_;
}

ULevelTransitionManager* UIKGameInstance::GetLevelTransitionManager() noexcept
{
	return level_transition_manager_;
}

void UIKGameInstance::InitializeCharacterDataManager()
{
	character_data_manager_ = NewObject<UCharacterDataManager>();
}

void UIKGameInstance::InitializeItemInventory()
{
	item_inventory_ = NewObject<UItemInventory>();
}

void UIKGameInstance::InitializeMaps()
{
	maps_ = NewObject<UIKMaps>();
	maps_->GenerateMaps(7, 4);
}

void UIKGameInstance::InitializeLevelTransitionManager()
{
	level_transition_manager_ = NewObject<ULevelTransitionManager>();
	level_transition_manager_->SetActorBlueprints(hero_blueprint_, enemy_blueprint_);
}
