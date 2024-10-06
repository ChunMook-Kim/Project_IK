/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.19.2024
Summary : Header file for Game Instance. It is used to initialize game app.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "IKGameInstance.generated.h"

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

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UIKGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UIKGameInstance();

	FCharacterData* GetCharacterData(int32 char_id);

	virtual void Init() override;

private:
	UPROPERTY()
	class UDataTable* character_table;
};
