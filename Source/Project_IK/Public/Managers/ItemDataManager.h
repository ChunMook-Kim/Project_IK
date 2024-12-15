/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.27.2024
Summary : Header file for Manager that controls item data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemDataManager.generated.h"

enum class ETargetingMode : uint8;
enum class ETargetType : uint8;

UENUM(BlueprintType)
enum class EItemLogicType : uint8
{
	None UMETA(DisplayName = "None"),
	RestoreHP UMETA(DisplayName = "RestoreHP"),
	LaunchMissile UMETA(DisplayName = "LaunchMissile"),
	AttackSpeedStimuli UMETA(DisplayName = "AttackSpeedStimuli"),
	SmokeGrenade UMETA(DisplayName = "SmokeGrenade"),
	Flashbang UMETA(DisplayName = "Flashbang"),
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Item")
	FString item_name_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	UTexture2D* item_icon_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FString item_description_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemLogicType item_logic_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	ETargetingMode targeting_mode_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	ETargetType target_type_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	float range_;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	float radius_;
};

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UItemDataManager : public UObject
{
	GENERATED_BODY()
public:
	UItemDataManager();

	FItemData* GetItemData(int32 item_id) const;
	FItemData* GetItemDataRandomly() const;

protected:
	class UDataTable* item_table_;
};
