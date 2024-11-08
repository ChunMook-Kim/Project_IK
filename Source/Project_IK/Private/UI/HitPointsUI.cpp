// Fill out your copyright notice in the Description page of Project Settings.


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
