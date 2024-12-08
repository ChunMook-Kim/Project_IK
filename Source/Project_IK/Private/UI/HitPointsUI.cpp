/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.13.2024
Summary : Source file for Skill Bar UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/HitPointsUI.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CharacterStatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

#include "UI/BuffDisplayer.h"

void UHitPointsUI::BindCharacterStat(UCharacterStatComponent* NewCharacterStat)
{
	if (NewCharacterStat)
	{
		character_stat_ = NewCharacterStat;

		character_stat_->OnHPChanged.AddDynamic(this, &UHitPointsUI::UpdateHPWidget);
	}
}

void UHitPointsUI::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeImages();

	UpdateHPWidget();
}

void UHitPointsUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	UpdateBuffWidgets();
}

void UHitPointsUI::UpdateHPWidget()
{
	if (character_stat_.IsValid())
	{
		if (hp_progress_bar_.Get())
		{
			hp_progress_bar_->SetPercent(character_stat_->GetHPRatio());
		}
	}
}

void UHitPointsUI::UpdateBuffWidgets()
{
	if (character_stat_.IsValid())
	{
		const TArray<FBuff> buffs = character_stat_->GetBuffs();

		TMap<ECharacterStatType, TPair<int32, UTexture2D*>> buff_counts;
		for (const FBuff& buff : buffs)
		{
			if (buff_counts.Contains(buff.stat_type_))
			{
				buff_counts[buff.stat_type_].Key += 1;
			}
			else
			{
				buff_counts.Add(buff.stat_type_, TPair<int32, UTexture2D*>(1, buff.buff_icon_));
			}
		}

		int i = 0;
		for (auto buff_count : buff_counts)
		{
			if (buff_displayers_[i]->GetVisibility() != ESlateVisibility::Visible)
			{
				buff_displayers_[i]->SetVisibility(ESlateVisibility::Visible);
			}
			buff_displayers_[i]->SetImage(buff_count.Value.Value);
			
			if (buff_count.Value.Key > 1)
			{
				buff_displayers_[i]->SetDuplicatedText(buff_count.Value.Key);
			}
			else
			{
				buff_displayers_[i]->HideText();
			}

			++i;
		}
		for (; i < DISPLAYER_SIZE; ++i)
		{
			if (buff_displayers_[i]->GetVisibility() != ESlateVisibility::Collapsed)
			{
				buff_displayers_[i]->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}

void UHitPointsUI::InitializeImages()
{
	for (int32 i = 0; i < DISPLAYER_SIZE; i++)
	{
		UBuffDisplayer* buff_displayer = WidgetTree->ConstructWidget<UBuffDisplayer>();
		UHorizontalBoxSlot* displayer_slot = buffs_container_->AddChildToHorizontalBox(buff_displayer);

		buff_displayers_.Add(buff_displayer);
	}
}
