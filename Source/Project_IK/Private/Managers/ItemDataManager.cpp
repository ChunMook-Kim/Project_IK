/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.27.2024
Summary : Source file for Manager that controls item data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/ItemDataManager.h"
#include "Components/TargetingComponent.h"

UItemDataManager::UItemDataManager()
	:Super::UObject()
{
	FString item_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Proto_ItemData.IK_Proto_ItemData'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_item_data(*item_data_path);
	if (dt_item_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a game file data (IK_Proto_ItemData)"));
	}
	item_table_= dt_item_data.Object;
}

FItemData* UItemDataManager::GetItemData(int32 item_id) const
{
	if (item_table_)
	{
		return item_table_->FindRow<FItemData>(*FString::FromInt(item_id), TEXT(""));
	}
	return nullptr;
}

FItemData* UItemDataManager::GetItemDataRandomly() const
{
	if (item_table_)
	{
		TArray<FName> row_names = item_table_->GetRowNames();
		if (row_names.Num() <= 0)
		{
			return nullptr;
		}
		int32 queried_index = FMath::RandRange(0, row_names.Num() - 1);
		return item_table_->FindRow<FItemData>(row_names[queried_index], TEXT(""));
	}
	return nullptr;
}
