/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.17.2024
Summary : Source file for Combat Result UI class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/CombatResultUI.h"

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
#include "UI/CombatResultBlock.h"

bool UCombatResultUI::Initialize()
{
	bool success = Super::Initialize();
	if (!success)
	{
		return false;
	}

	InitializeRootWidget();

	return true;
}

void UCombatResultUI::SetHeroNumbers(int32 num)
{
	UCanvasPanelSlot* UI_background_slot = Cast<UCanvasPanelSlot>(UI_background_->Slot);
	if (UI_background_slot)
	{
		UI_background_slot->SetPosition(FVector2D(num * -200.0, -400.0));
		UI_background_slot->SetSize(FVector2D(num * 400.0, 800.0));
	}

	for (int32 i = 0; i < num; i++)
	{
		UCombatResultBlock* block = NewObject<UCombatResultBlock>();
		FString block_unique_name = MakeUniqueObjectName(GetOuter(), block->GetClass(), TEXT("Block")).ToString();
		block->Rename(*block_unique_name);
		UHorizontalBoxSlot* block_slot = blocks_holder_->AddChildToHorizontalBox(block);
		block_slot->SetPadding(FMargin(32.f));
	}
}

void UCombatResultUI::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeChildWidgets();
}

void UCombatResultUI::InitializeRootWidget()
{
	root_canvas_panel_ = WidgetTree->ConstructWidget<UCanvasPanel>();
	root_canvas_panel_->Rename(TEXT("Root canvas panel"));
	WidgetTree->RootWidget = root_canvas_panel_.Get();
}

void UCombatResultUI::InitializeChildWidgets()
{
	// Initialize outlines
	UI_background_ = NewObject<UBorder>();
	UI_background_->Rename(TEXT("UI Background"));
	UI_background_->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	UI_background_->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.4f));
	UCanvasPanelSlot* UI_background_slot = root_canvas_panel_->AddChildToCanvas(UI_background_.Get());
	if (UI_background_slot)
	{
		UI_background_slot->SetAnchors(FAnchors(0.5f, 0.5f));
	}

	widgets_holder_ = NewObject<UVerticalBox>();
	widgets_holder_->Rename(TEXT("Widgets holder"));
	UBorderSlot* widgets_holder_slot = Cast<UBorderSlot>(UI_background_->AddChild(widgets_holder_.Get()));
	if (widgets_holder_slot)
	{
		widgets_holder_slot->SetPadding(FMargin(4.0, 2.0));
		widgets_holder_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	}


	// Initialize title texts
	title_holder_ = NewObject<UBorder>();
	title_holder_->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	title_holder_->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	title_holder_->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.f));
	UVerticalBoxSlot* title_holder_slot = widgets_holder_->AddChildToVerticalBox(title_holder_.Get());
	if (title_holder_slot)
	{
		title_holder_slot->SetPadding(FMargin(0.0, 64.0, 0.0, -64.0));
	}
	
	title_ = NewObject<UTextBlock>();
	title_->SetText(FText::FromString("Combat Result"));
	UBorderSlot* title_slot = Cast<UBorderSlot>(title_holder_->AddChild(title_.Get()));
	if (title_slot)
	{
		title_slot->SetPadding(FMargin(4.0f, 2.0f));
		title_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		title_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}
	
	// Initialize a block holder
	blocks_holder_ = NewObject<UHorizontalBox>();
	UVerticalBoxSlot* blocks_holder_slot = widgets_holder_->AddChildToVerticalBox(blocks_holder_.Get());
	if (blocks_holder_slot)
	{
		blocks_holder_slot->SetSize(FSlateChildSize());
		blocks_holder_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		blocks_holder_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}
}
