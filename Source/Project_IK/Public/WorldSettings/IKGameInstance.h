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
#include "Engine/GameInstance.h"


#include "IKGameInstance.generated.h"

class UItemInventory;
class UIKMaps;
class UCharacterDataManager;
class UItemDataManager;
class ULevelTransitionManager;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UIKGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UIKGameInstance();

	virtual void Init() override;

	UFUNCTION(BlueprintPure)
	const class UItemDataManager* GetItemDataManager() noexcept;
	UFUNCTION(BlueprintPure)
	const class UCharacterDataManager* GetCharacterDataManager() noexcept;
	UFUNCTION(BlueprintPure)
	class UItemInventory* GetItemInventory() const noexcept;
	UFUNCTION(BlueprintPure)
	const class UIKMaps* GetMapPtr() const noexcept;
	UFUNCTION(BlueprintPure)
	class ULevelTransitionManager* GetLevelTransitionManager() noexcept;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelTransition")
	TSubclassOf<AActor> hero_blueprint_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelTransition")
	TSubclassOf<AActor> enemy_blueprint_;

private:
	void InitializeItemDataManager();
	void InitializeCharacterDataManager();
	void InitializeItemInventory();
	void InitializeMaps();
	void InitializeLevelTransitionManager();

	UPROPERTY()
	class UItemDataManager* item_data_manager_;
	UPROPERTY()
	class UCharacterDataManager* character_data_manager_;
	UPROPERTY()
	class UItemInventory* item_inventory_;

	UPROPERTY()
	class UIKMaps* maps_;

	UPROPERTY()
	class ULevelTransitionManager* level_transition_manager_;
};
