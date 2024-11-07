// Fill out your copyright notice in the Description page of Project Settings.


#include "IKGameInstance.h"

#include "ItemInventory.h"
#include "IKMaps.h"
#include "MyTestItem.h"

UIKGameInstance::UIKGameInstance()
{
	InitializeCharacterData();
	InitializeItemInventory();
	InitializeMaps();
}

FCharacterData* UIKGameInstance::GetCharacterData(int32 char_id) const
{
	if(character_table)
	{
		return character_table->FindRow<FCharacterData>(*FString::FromInt(char_id), TEXT(""));
	}
	return nullptr;
}

void UIKGameInstance::Init()
{
	Super::Init();

	item_inventory_->AddItem(UMyTestItem::StaticClass());
}

UItemInventory* UIKGameInstance::GetItemInventory() const noexcept
{
	return item_inventory_;
}

const UIKMaps* UIKGameInstance::GetMapPtr() const
{
	return maps_;
}

void UIKGameInstance::InitializeCharacterData()
{
	FString character_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Proto_GameData.IK_Proto_GameData'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_character_data(*character_data_path);
	if (dt_character_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a game file data (IK_Proto_GameData)"));
	}
	character_table = dt_character_data.Object;
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
