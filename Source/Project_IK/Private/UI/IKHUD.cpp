/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for HUD class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/IKHUD.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"

#include "UI/CombatResultUI.h"
#include "Managers/LevelEndUIManager.h"

void AIKHUD::DisplayCombatResult(const TArray<AActor*>& heroes, const TMap<TWeakObjectPtr<AActor>, float>& damage_map)
{
	if (level_end_ui_manager_.IsValid())
	{
		level_end_ui_manager_->DisplayCombatResult(heroes, damage_map);
	}
}

void AIKHUD::SwitchUIByState(ELevelEndState state)
{
	if (level_end_ui_manager_.IsValid())
	{
		level_end_ui_manager_->SwitchUIByState(state);
	}
}

void AIKHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();

	// Create the widget and add it to the viewport
	if (HUD_widget_class_)
	{
		HUD_widget_ = CreateWidget<UUserWidget>(world, HUD_widget_class_);
		if (HUD_widget_.IsValid())
		{
			HUD_widget_->AddToViewport();
		}
	}

	level_end_ui_manager_ = NewObject<ULevelEndUIManager>();
	if (level_end_ui_manager_.IsValid())
	{
		level_end_ui_manager_->InitializeUI(combat_result_widget_class_, map_widget_class_, world);
	}
}
