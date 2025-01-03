/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.3.2025
Summary : Source file for a user widget to display gotcha result.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/GotchaResultWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/Image.h"

void UGotchaResultWidget::DisplayResults(TArray<UTexture2D*> textures)
{
	for (int32 i = 0; i < MAX_IMAGE; i++)
	{
		images_[i]->SetBrushResourceObject(textures[i]);
	}
}

void UGotchaResultWidget::DisplayResult(UTexture2D* texture)
{
	images_[0]->SetBrushResourceObject(texture);
	UGridSlot* grid_slot = Cast<UGridSlot>(images_[0]->Slot);
	grid_slot->SetNudge(FVector2D(600.f, 150.f));

	for (int32 i = 1; i < MAX_IMAGE; i++)
	{
		images_[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UGotchaResultWidget::NativeConstruct()
{
	FSlateBrush default_brush;
	default_brush.DrawAs = ESlateBrushDrawType::Type::Image;
	default_brush.SetImageSize(FVector2D(128.0));
	
	for (int32 i = 0; i < MAX_IMAGE; i++)
	{
		UImage* image = WidgetTree->ConstructWidget<UImage>();
		image->SetBrush(default_brush);
		UGridSlot* grid_slot = image_containers_->AddChildToGrid(image);
		if (grid_slot)
		{
			grid_slot->SetPadding(FMargin(86));
			grid_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			grid_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			grid_slot->SetColumn(i % 5);
			grid_slot->SetRow(i / 5);
		}

		images_.Add(image);
	}
}
