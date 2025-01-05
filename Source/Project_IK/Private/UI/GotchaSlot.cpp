/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.5.2025
Summary : Source file for a gotcha slot.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/GotchaSlot.h"

#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"


void UGotchaSlot::SetImage(UTexture2D* texture)
{
	slot_image_->SetBrushResourceObject(texture);
}

UWidgetAnimation* UGotchaSlot::GetAnimation()
{
	return slot_animation_;
}

void UGotchaSlot::ResetAnimationStatus()
{
	slot_image_->SetRenderScale(FVector2D(0.f, 0.f));
}

void UGotchaSlot::NativeConstruct()
{
	FSlateBrush default_brush;
	default_brush.DrawAs = ESlateBrushDrawType::Type::Image;
	default_brush.SetImageSize(FVector2D(128.0));

	slot_image_->SetBrush(default_brush);
}
