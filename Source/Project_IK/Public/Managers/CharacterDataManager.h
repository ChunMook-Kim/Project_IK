/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.10.2024
Summary : Header file for managing characters data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "CharacterDataManager.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCharacterData() : ability_power_(0.f), attack_(0.f), attack_speed_(0.f), hit_point_(0.f), magazine_(0.f),
		fire_range_(0.f), move_speed_(0.f), sight_range_(0.f)
	{};

	// Scaling powers
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float ability_power_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float attack_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float attack_speed_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float hit_point_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float magazine_;

	// Fixed powers
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float fire_range_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float move_speed_;
	UPROPERTY(VisibleAnywhere, Category = "Data")
	float sight_range_;
};

UCLASS()
class PROJECT_IK_API UCharacterDataManager : public UObject
{
	GENERATED_BODY()
public:
	UCharacterDataManager();

	FCharacterData* GetCharacterData(int32 char_id) const;

protected:
	class UDataTable* character_table;
};