/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.13.2024
Summary : Source file for Skill Bar UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/HitPointsUI.h"

#include "Components/CharacterStatComponent.h"
#include "Components/ProgressBar.h"

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

	UpdateHPWidget();
}

void UHitPointsUI::UpdateHPWidget()
{
	if (character_stat_.IsValid())
	{
		if (hp_progress_bar_)
		{
			hp_progress_bar_->SetPercent(character_stat_->GetHPRatio());
		}
	}
}
