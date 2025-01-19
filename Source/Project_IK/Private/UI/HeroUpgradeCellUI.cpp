// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HeroUpgradeCellUI.h"

#include "Components/SizeBox.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "Blueprint/WidgetTree.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/HorizontalBox.h"
#include "Rendering/DrawElements.h"


UHeroUpgradeCellUI::UHeroUpgradeCellUI(const FObjectInitializer& object_initializer)
	: Super::UUserWidget(object_initializer)
{
}

bool UHeroUpgradeCellUI::Initialize()
{
	Super::Initialize();
	buttons_.Add(level_1);
	buttons_.Add(level_2);
	buttons_.Add(level_3);
	buttons_.Add(level_4);
	buttons_.Add(level_5);
	return true;
}

void UHeroUpgradeCellUI::NativeConstruct()
{
	Super::NativeConstruct();
	buttons_.Empty();
	buttons_.Add(level_1);
	buttons_.Add(level_2);
	buttons_.Add(level_3);
	buttons_.Add(level_4);
	buttons_.Add(level_5);
}

void UHeroUpgradeCellUI::NativeDestruct()
{
	buttons_.Empty();
	Super::NativeDestruct();
}

// FVector2D UHeroUpgradeCellUI::GetButtonPosition(UButton* button) const
// {
// 	return background_border_->GetPaintSpaceGeometry().
// 	GetLocalPositionAtCoordinates(
// 		FVector2D(0.0f)) +
// 			scroll_box_->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0f))
// 	+ button->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0)) - FVector2D(0.0, scroll_box_->GetScrollOffset())
// 	+ (button->GetPaintSpaceGeometry().GetLocalSize() / 2.f);
// }
FVector2D UHeroUpgradeCellUI::GetButtonPosition(UButton* button) const
{
	return button_holder_->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0))
		+ button->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0))
		+ (button->GetPaintSpaceGeometry().GetLocalSize() / 2.f);
}

int32 UHeroUpgradeCellUI::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                      const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
                                      const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 CurrentLayer = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                          bParentEnabled);

	// Define the start and end points for the line
	FVector2D StartPoint = FVector2D(0, 0);  // Top-left corner
	FVector2D EndPoint = AllottedGeometry.GetLocalSize();  // Bottom-right corner based on widget size

	// Define color and thickness
	FLinearColor LineColor = FLinearColor::Red * 0.4f;
	float LineThickness = 5.0f;

	FSlateClippingZone clipping_zone(size_box_->GetPaintSpaceGeometry());
	OutDrawElements.PushClip(clipping_zone);
	TArray<FVector2D> lines;

	for(int i = 0; i < 4; ++i)
	{
		lines.Add(GetButtonPosition(buttons_[i]));
		lines.Add(GetButtonPosition(buttons_[i + 1]));
		//-55는 현재 상황에서 작동하는 Magic number이다. 이후 알고리즘을 찾아야 한다.
		static constexpr int32 DrawBelowButtons = -55;

		FSlateDrawElement::MakeLines(OutDrawElements, CurrentLayer + DrawBelowButtons, AllottedGeometry.ToPaintGeometry(), lines, ESlateDrawEffect::None, LineColor, true, LineThickness);
	}
	OutDrawElements.PopClip();

	return CurrentLayer;
}