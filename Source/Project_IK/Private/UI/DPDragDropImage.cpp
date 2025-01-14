/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 1.10.2025
Summary : Source file for the Drag Drop image for inventory.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/DPDragDropImage.h"

#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UDPDragDropImage::NativePreConstruct()
{
	Super::NativePreConstruct();
}

FReply UDPDragDropImage::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	if(InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		return ReplyResult.NativeReply;
	}
	return FReply::Unhandled();
}

void UDPDragDropImage::SetImage(UTexture2D* input_texture)
{
	dragged_image_->SetBrushFromTexture(input_texture);
}
