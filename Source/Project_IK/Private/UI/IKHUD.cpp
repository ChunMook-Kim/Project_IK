/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for HUD class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/IKHUD.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

void AIKHUD::BeginPlay()
{
	Super::BeginPlay();

	// Create the widget and add it to the viewport
	HUD_widget_ = CreateWidget<UUserWidget>(GetWorld(), HUD_widget_class_);
	if (HUD_widget_)
	{
		HUD_widget_->AddToViewport();
	}
}
