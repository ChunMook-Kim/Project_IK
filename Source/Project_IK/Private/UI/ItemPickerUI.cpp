/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.25.2024
Summary : Source file for UI to pick an item.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/ItemPickerUI.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"


bool UItemPickerUI::Initialize()
{
	bool success = Super::Initialize();
	if (!success)
	{
		return success;
	}

	InitializeRootWidget();

	return true;
}

void UItemPickerUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UItemPickerUI::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeChildWidgets();
}

void UItemPickerUI::InitializeRootWidget()
{
	root_canvas_panel_ = WidgetTree->ConstructWidget<UCanvasPanel>();
	WidgetTree->RootWidget = root_canvas_panel_.Get();
}

void UItemPickerUI::InitializeChildWidgets()
{
	background_ = NewObject<UBorder>();
	background_->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	background_->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.4f));
	UCanvasPanelSlot* background_slot = root_canvas_panel_->AddChildToCanvas(background_.Get());
	if (background_slot)
	{
		background_slot->SetAnchors(FAnchors(0.5f, 0.5f));
		background_slot->SetSize(FVector2D(900.0, 800.0));
		background_slot->SetPosition(FVector2D(-450.0, -400.0));
	}

	widgets_holder_ = NewObject<UVerticalBox>();
	UBorderSlot* widgets_holder_slot = Cast<UBorderSlot>(background_->AddChild(widgets_holder_.Get()));
	if (widgets_holder_slot)
	{
		widgets_holder_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		widgets_holder_slot->SetPadding(FMargin());
	}

	title_ = NewObject<UTextBlock>();
	title_->SetText(FText::FromString("Take one of items"));
	FSlateFontInfo magnified_font = title_->Font;
	magnified_font.Size = 48;
	title_->SetFont(magnified_font);
	UVerticalBoxSlot* title_slot = widgets_holder_->AddChildToVerticalBox(title_.Get());
	if (title_slot)
	{
		title_slot->SetPadding(FMargin(0.f, 32.f));
		title_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		title_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}

	description_ = NewObject<UTextBlock>();
	description_->SetText(FText::FromString("Descriptions of a selected item will be shown here.\nPick up one of them."));
	description_->SetAutoWrapText(true);
	UVerticalBoxSlot* description_slot = widgets_holder_->AddChildToVerticalBox(description_.Get());
	if (description_slot)
	{
		description_slot->SetPadding(FMargin(32.0, 0.0));
		description_slot->SetSize(FSlateChildSize(ESlateSizeRule::Type::Fill));
	}

	buttons_holder_ = NewObject<UHorizontalBox>();
	UVerticalBoxSlot* buttons_holder_slot = widgets_holder_->AddChildToVerticalBox(buttons_holder_.Get());
	if (buttons_holder_slot)
	{
		buttons_holder_slot->SetSize(FSlateChildSize(ESlateSizeRule::Type::Fill));
		buttons_holder_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		buttons_holder_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}

	UTexture2D* item_texture_placeholder = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/Images/enemy_icon.enemy_icon")));
	if (!item_texture_placeholder)
	{
		return;
	}

	for (int32 i = 0; i < 3; i++)
	{
		TWeakObjectPtr<UButton> button = NewObject<UButton>();
		FSlateBrush new_brush;
		new_brush.SetResourceObject(item_texture_placeholder);
		new_brush.DrawAs = ESlateBrushDrawType::Type::Image;
		new_brush.TintColor = FSlateColor(FLinearColor(0.69f, 0.69f, 0.69f));
		new_brush.SetImageSize(FVector2D(128.0, 128.0));
		button->WidgetStyle.SetNormal(new_brush);
		new_brush.TintColor = FSlateColor(FLinearColor(0.95f, 0.95f, 0.95f));
		button->WidgetStyle.SetHovered(new_brush);
		new_brush.TintColor = FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f));
		button->WidgetStyle.SetPressed(new_brush);
		UHorizontalBoxSlot* button_slot = buttons_holder_->AddChildToHorizontalBox(button.Get());

		if (button_slot)
		{
			button_slot->SetPadding(FMargin(64.0, 0.0));
		}
		buttons_.Add(button);
	}


	UTexture2D* select_texture_placeholder = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/Images/enemy_icon.enemy_icon")));
	select_button_ = NewObject<UButton>();
	FSlateBrush select_brush;
	select_brush.SetResourceObject(select_texture_placeholder);
	select_brush.DrawAs = ESlateBrushDrawType::Type::Image;
	select_brush.TintColor = FSlateColor(FLinearColor(0.69f, 0.69f, 0.69f));
	select_brush.SetImageSize(FVector2D(256.0, 64.0));
	select_button_->WidgetStyle.SetNormal(select_brush);
	select_brush.TintColor = FSlateColor(FLinearColor(0.95f, 0.95f, 0.95f));
	select_button_->WidgetStyle.SetHovered(select_brush);
	select_brush.TintColor = FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f));
	select_button_->WidgetStyle.SetPressed(select_brush);
	UVerticalBoxSlot* select_button_slot = widgets_holder_->AddChildToVerticalBox(select_button_.Get());
	if (select_button_slot)
	{
		select_button_slot->SetPadding(FMargin(0.0, 0.0, 0.0, 32.0));
		select_button_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		select_button_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}
}
