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
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"

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

		int32 loop_until = FMath::Min(IMAGE_SIZE, buffs.Num());
		for (int32 i = 0; i < loop_until; ++i)
		{
			buff_images_[i]->SetBrushFromTexture(buffs[i].buff_icon_);
		}
		for (int32 i = loop_until; i < IMAGE_SIZE; ++i)
		{
			buff_images_[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UHitPointsUI::InitializeImages()
{
	FSlateBrush brush;
	brush.DrawAs = ESlateBrushDrawType::Image;
	brush.SetImageSize(FVector2D(32.0));

	for (int32 i = 0; i < IMAGE_SIZE; i++)
	{
		UImage* image = NewObject<UImage>();
		image->SetBrush(brush);
		buffs_container_->AddChild(image);

		buff_images_.Add(image);
	}
}
