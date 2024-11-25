/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.05.2024
Summary : Source file for displaying maps.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/MapWidget.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Project_IK/Public/WorldSettings/IKGameInstance.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Components/ScrollBox.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/Button.h"

#include "Blueprint/WidgetTree.h"
#include "Rendering/DrawElements.h"

#include "Managers/LevelTransitionManager.h"

#include "UI/IKMaps.h"

UMapWidget::UMapWidget(const FObjectInitializer& object_initializer)
	: Super::UUserWidget(object_initializer)
{
	root_canvas_panel_ = nullptr;
	maps_ = nullptr;
}

bool UMapWidget::Initialize()
{
	bool success = Super::Initialize();
	if (!success)
	{
		return false;
	}

	// I don't know reason why but it should be in this function.
	InitializeWidgetTree();


	return true;
}

int32 UMapWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	// Call the parent implementation first
	int32 CurrentLayer = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	// Define the start and end points for the line
	FVector2D StartPoint = FVector2D(0, 0);  // Top-left corner
	FVector2D EndPoint = AllottedGeometry.GetLocalSize();  // Bottom-right corner based on widget size

	// Define color and thickness
	FLinearColor LineColor = FLinearColor::Red;
	float LineThickness = 5.0f;
	
	FSlateClippingZone clipping_zone(scroll_box_->GetPaintSpaceGeometry());
	OutDrawElements.PushClip(clipping_zone);

	for (int32 i = 0; i < maps_->GetHeight(); ++i)
	{
		for (int32 j = 0; j < maps_->GetWidth(); ++j)
		{

			const FMapNode& node = maps_->GetNode(i, j);
			for (int32 k = 0; k < node.next.Num(); k++)
			{
				TArray<FVector2D> line;
				
				TWeakObjectPtr<UButton> departures = buttons_[FIntPoint(i, j)];
				line.Add(GetButtonPosition(departures));
				TWeakObjectPtr<UButton> arrivals = buttons_[FIntPoint(i + 1, node.next[k])];
				line.Add(GetButtonPosition(arrivals));

				if (!departures->GetPaintSpaceGeometry().GetLocalSize().IsNearlyZero() && !arrivals->GetPaintSpaceGeometry().GetLocalSize().IsNearlyZero())
				{
					FSlateDrawElement::MakeLines(OutDrawElements, CurrentLayer, AllottedGeometry.ToPaintGeometry(), line, ESlateDrawEffect::None, LineColor, true, LineThickness);
				}
			}
		}
	}
	OutDrawElements.PopClip();

	// Increase the layer ID if you plan to add more elements later
	return CurrentLayer + 1;
}

void UMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeWidgets();
}

void UMapWidget::InitializeWidgetTree()
{
	root_canvas_panel_ = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("MapWidgetRootCanvas"));
	WidgetTree->RootWidget = root_canvas_panel_.Get();
}

void UMapWidget::InitializeButtons()
{
	buttons_.Empty();

	UTexture2D* enemy_icon_texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Game/Images/enemy_icon.enemy_icon")));
	if (!enemy_icon_texture)
	{
		return;
	}

	auto ik_game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	FVector2D button_size(50.f, 50.f);

	if (ik_game_instance)
	{
		maps_ = ik_game_instance->GetMapPtr();

		if (maps_.Get())
		{
			for (int32 i = 0; i < maps_->GetHeight(); i++)
			{
				for (int32 j = 0; j < maps_->GetWidth(); j++)
				{
					const FMapNode& node = maps_->GetNode(i, j);
					
					if (node.type == NodeType::None)
					{
						continue;
					}

					// Init buttons
					UButton* button = NewObject<UButton>();
					FSlateBrush new_brush;
					new_brush.SetResourceObject(enemy_icon_texture);
					new_brush.DrawAs = ESlateBrushDrawType::Type::Image;
					new_brush.TintColor = FSlateColor(FLinearColor(0.69f, 0.69f, 0.69f));
					new_brush.SetImageSize(FDeprecateSlateVector2D(128.f, 128.f));
					button->WidgetStyle.SetNormal(new_brush);
					new_brush.TintColor = FSlateColor(FLinearColor(0.95f, 0.95f, 0.95f));
					button->WidgetStyle.SetHovered(new_brush);
					new_brush.TintColor = FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f));
					button->WidgetStyle.SetPressed(new_brush);
					UGridSlot* button_slot = buttons_holder_->AddChildToGrid(button);
					if (button_slot)
					{
						button_slot->SetPadding(FMargin(32.f));
						button_slot->SetColumn(j);
						button_slot->SetRow(maps_->GetHeight() - 1 - i);
					}

					button->OnClicked.AddDynamic(this, &UMapWidget::OpenLevel);

					buttons_.Add(FIntPoint(i, j), button);
				}
			}

		}
	}
}

void UMapWidget::InitializeWidgets()
{
	background_border_ = NewObject<UBorder>();
	background_border_->Rename(*MakeUniqueObjectName(GetOuter(), background_border_->GetClass(), TEXT("Background")).ToString());
	background_border_->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	background_border_->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.4f));
	UCanvasPanelSlot* background_border_slot = root_canvas_panel_->AddChildToCanvas(background_border_.Get());
	background_border_slot->SetAnchors(FAnchors(0.5f, 0.5f));
	background_border_slot->SetPosition(FVector2D(-800.0, -400.0));
	background_border_slot->SetSize(FVector2D(1600.0, 800.0));

	scroll_box_ = NewObject<UScrollBox>();
	scroll_box_->Rename(*MakeUniqueObjectName(GetOuter(), scroll_box_->GetClass(), TEXT("ScrollBox")).ToString());
	UBorderSlot* scroll_box_slot = Cast<UBorderSlot>(background_border_->AddChild(scroll_box_.Get()));
	scroll_box_slot->SetPadding(FMargin(0.f, 32.f));
	scroll_box_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	scroll_box_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);

	buttons_holder_ = NewObject<UGridPanel>();
	buttons_holder_->Rename(*MakeUniqueObjectName(GetOuter(), scroll_box_->GetClass(), TEXT("Buttons Holder")).ToString());
	scroll_box_->AddChild(buttons_holder_.Get());

	InitializeButtons();
}

FVector2D UMapWidget::GetButtonPosition(TWeakObjectPtr<UButton> button) const
{
	return background_border_->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0f)) + scroll_box_->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0f)) + button->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0)) - FVector2D(0.0, scroll_box_->GetScrollOffset()) + (button->GetPaintSpaceGeometry().GetLocalSize() / 2.f);
}

void UMapWidget::OpenLevel()
{
	UWorld* world = GetWorld();
	Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(world))->GetLevelTransitionManager()->OpenLevel(FName("CombatLevel"), world);
}
