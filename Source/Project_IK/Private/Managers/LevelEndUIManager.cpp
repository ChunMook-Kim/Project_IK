// Fill out your copyright notice in the Description page of Project Settings.


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
		}
	}
}

void ULevelEndUIManager::ToggleMapWidget()
{
	if (map_widget_.IsValid())
	{
		const bool is_visible = map_widget_->IsVisible();
		map_widget_->SetVisibility(is_visible ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	}
}

void ULevelEndUIManager::DisplayCombatResult(const TArray<AActor*>& heroes, const TMap<TWeakObjectPtr<AActor>, float>& damage_map)
{
	combat_result_widget_->SetVisibility(ESlateVisibility::Visible);
	combat_result_widget_->UpdateResults(heroes, damage_map);
}
