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

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/TextureManager.h"

void UHitPointsUI::BindCharacterStat(UCharacterStatComponent* NewCharacterStat)
{
	if (NewCharacterStat)
	{
		character_stat_ = NewCharacterStat;

		character_stat_->OnHPChanged.AddDynamic(this, &UHitPointsUI::UpdateHPWidget);
		character_stat_->OnShieldChanged.AddDynamic(this, &UHitPointsUI::UpdateShieldWidget);
	}
}

void UHitPointsUI::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeImages();

	UpdateHPWidget();
	UpdateShieldWidget();

	texture_manager_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetTextureManager();
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

void UHitPointsUI::UpdateShieldWidget()
{
	if (character_stat_.IsValid())
	{
		if (shield_progress_bar_.Get())
		{
			if (character_stat_->GetShield() <= 0.f)
			{
				shield_progress_bar_->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				shield_progress_bar_->SetPercent(character_stat_->GetShieldRatio());
				if (shield_progress_bar_->GetVisibility() != ESlateVisibility::Visible)
				{
					shield_progress_bar_->SetVisibility(ESlateVisibility::Visible);
				}
			}

		}
	}
}

void UHitPointsUI::UpdateBuffWidgets()
{
	if (character_stat_.IsValid())
	{
		const TArray<FBuff> buffs = character_stat_->GetBuffs();

		TMap<ECharacterStatType, int32> buff_counts;
		for (const FBuff& buff : buffs)
		{
			if (buff_counts.Contains(buff.stat_type_))
			{
				buff_counts[buff.stat_type_] += 1;
			}
			else
			{
				buff_counts.Add(buff.stat_type_, 1);
			}
		}

		int i = 0;
		for (auto buff_count : buff_counts)
		{
			if (buff_displayers_[i]->GetVisibility() != ESlateVisibility::Visible)
			{
				buff_displayers_[i]->SetVisibility(ESlateVisibility::Visible);
			}
			buff_displayers_[i]->SetImage(texture_manager_->GetBuffTexture(buff_count.Key));
			buff_displayers_[i]->SetBackground(FLinearColor::Green);
			
			if (buff_count.Value > 1)
			{
				buff_displayers_[i]->SetDuplicatedText(buff_count.Value);
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
		UBuffDisplayer* buff_displayer = WidgetTree->ConstructWidget<UBuffDisplayer>(buff_displayer_class_);
		UHorizontalBoxSlot* displayer_slot = buffs_container_->AddChildToHorizontalBox(buff_displayer);

		buff_displayers_.Add(buff_displayer);
	}
}
