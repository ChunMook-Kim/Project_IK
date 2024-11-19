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
#include "WorldSettings/IKGameModeBase.h"

#include "UI/CombatResultUI.h"

void AIKHUD::ToggleMapWidget()
{
	if (map_widget_)
	{
		const bool is_visible = map_widget_->IsVisible();
		map_widget_->SetVisibility(is_visible ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	}
}

void AIKHUD::DisplayCombatResult(const TArray<AActor*>& heroes, const TMap<TWeakObjectPtr<AActor>, float>& damage_map)
{
	combat_result_widget_->SetVisibility(ESlateVisibility::Visible);
	combat_result_widget_->UpdateResults(heroes, damage_map);
}

void AIKHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();

	// Create the widget and add it to the viewport
	if (HUD_widget_class_)
	{
		HUD_widget_ = CreateWidget<UUserWidget>(world, HUD_widget_class_);
		if (HUD_widget_)
		{
			HUD_widget_->AddToViewport();
		}
	}

	if (combat_result_widget_class_)
	{
		combat_result_widget_ = CreateWidget<UCombatResultUI>(world, combat_result_widget_class_);
		if (combat_result_widget_)
		{
			combat_result_widget_->AddToViewport();
			int32 hero_size = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this))->GetHeroContainers().Num();
			combat_result_widget_->SetHeroNumbers(hero_size);
			combat_result_widget_->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (map_widget_class_)
	{
		map_widget_ = CreateWidget<UUserWidget>(world, map_widget_class_);
		if (map_widget_)
		{
			map_widget_->AddToViewport();
		}
	}
}
