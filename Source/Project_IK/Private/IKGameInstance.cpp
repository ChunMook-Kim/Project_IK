// Fill out your copyright notice in the Description page of Project Settings.


#include "IKGameInstance.h"

#include "ItemInventory.h"
#include "IKMaps.h"
#include "MyTestItem.h"
#include "CharacterDataManager.h"

UIKGameInstance::UIKGameInstance()
{
	InitializeCharacterDataManager();
	InitializeItemInventory();
	InitializeMaps();
}

void UIKGameInstance::Init()
{
	Super::Init();

	item_inventory_->AddItem(UMyTestItem::StaticClass());
}

const UCharacterDataManager* UIKGameInstance::GetCharacterDataManager()
{
	return character_data_manager_;
}

UItemInventory* UIKGameInstance::GetItemInventory() const noexcept
{
	return item_inventory_;
}

const UIKMaps* UIKGameInstance::GetMapPtr() const
{
	return maps_;
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
