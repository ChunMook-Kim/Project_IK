/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.04.2024
Summary : Source file for structure that explain each of drone plugin.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/DronePluginManager.h"

UDronePluginManager::UDronePluginManager()
{
	FString dp_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Proto_DP_Data.IK_Proto_DP_Data'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_dp_data(*dp_data_path);
	if (dt_dp_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a dp file data (IK_Proto_Drone_Plugin_Data)"));
	}
	dp_table_= dt_dp_data.Object;
}

//BP에서는 struct의 pointer를 return할 수 없다. 그러므로, 복사본으로 넘긴다.
FDronePluginData UDronePluginManager::GetDPData(EDPType dp_id) const
{
	if (dp_table_)
	{
		return *dp_table_->FindRow<FDronePluginData>(*EnumToString(dp_id), TEXT(""));
	}
	return *dp_table_->FindRow<FDronePluginData>(*EnumToString(EDPType::Empty), TEXT(""));;
}

FString UDronePluginManager::EnumToString(EDPType dp_type) const
{
	FString dp_string;
	switch (dp_type)
	{
	case EDPType::FireRateBurst:
		dp_string = TEXT("FireRateBurst");
		break;
	case EDPType::FireRange:
		dp_string = TEXT("FireRange");
		break;
	case EDPType::HealingWaves:
		dp_string = TEXT("HealingWaves");
		break;
	case EDPType::LaserBeam:
		dp_string = TEXT("LaserBeam");
		break;
	default:
		dp_string = TEXT("Empty");
		break;
	}
	return dp_string;
}
