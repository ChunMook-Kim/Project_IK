/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.20.2024
Summary : Header file of a manager that handles UI controls after combats.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/LevelEndUIManager.h"

#include "Kismet/GameplayStatics.h"

#include "WorldSettings/IKGameModeBase.h"
#include "UI/CombatResultUI.h"

void ULevelEndUIManager::InitializeUI(TSubclassOf<class UCombatResultUI> combat_result_widget_class, TSubclassOf<class UUserWidget> map_widget_class, UWorld* world)
{

	if (combat_result_widget_class)
	{
		combat_result_widget_ = CreateWidget<UCombatResultUI>(world, combat_result_widget_class);
		if (combat_result_widget_.IsValid())
		{
			combat_result_widget_->AddToViewport();
			int32 hero_size = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(world))->GetHeroContainers().Num();
			combat_result_widget_->SetHeroNumbers(hero_size);
			combat_result_widget_->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (map_widget_class)
	{
		map_widget_ = CreateWidget<UUserWidget>(world, map_widget_class);
		if (map_widget_.IsValid())
		{
			map_widget_->AddToViewport();
			map_widget_->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ULevelEndUIManager::DisplayCombatResult(const TArray<AActor*>& heroes, const TMap<TWeakObjectPtr<AActor>, float>& damage_map)
{
	combat_result_widget_->SetVisibility(ESlateVisibility::Visible);
	combat_result_widget_->UpdateResults(heroes, damage_map);
}

void ULevelEndUIManager::SwitchUIByState(ELevelEndState state)
{
	switch (state)
	{
	case ELevelEndState::ShowingCombatResultUI:
		combat_result_widget_->SetVisibility(ESlateVisibility::Visible);
		map_widget_->SetVisibility(ESlateVisibility::Hidden);
		break;
	case ELevelEndState::ShowingMapUI:
		combat_result_widget_->SetVisibility(ESlateVisibility::Hidden);
		map_widget_->SetVisibility(ESlateVisibility::Visible);
		break;
	default:
		break;
	}
}
