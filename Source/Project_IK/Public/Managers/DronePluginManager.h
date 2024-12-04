/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.04.2024
Summary : Header file for structure that explain each of drone plugin.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Managers/EnumCluster.h"
#include "DronePluginManager.generated.h"

USTRUCT(BlueprintType)
struct FDronePluginData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DronePlugin")
	bool is_periodic_;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DronePlugin")
	UClass* dp_class_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DronePlugin")
	EDPType dp_type_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DronePlugin")
	UTexture2D* dp_icon_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DronePlugin")
	FString dp_description_;
};

UCLASS(Blueprintable)
class PROJECT_IK_API UDronePluginManager : public UObject
{
	GENERATED_BODY()
public:
	UDronePluginManager();
	
	UFUNCTION(BlueprintCallable, Category = "DronePluginManager")
	FDronePluginData GetDPData(EDPType dp_id) const;
	
	FString EnumToString(EDPType dp_type) const;
	
private:
	class UDataTable* dp_table_;
};