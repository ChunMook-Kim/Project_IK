/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.28.2024
Summary : Source file of HUD for Gotcha level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "WorldSettings/GotchaWorld/IKGotchaHUD.h"

#include "UI/GotchaWidget.h"

void AIKGotchaHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();

	if (gotcha_widget_class_)
	{
		gotcha_widget_ = CreateWidget<UGotchaWidget>(world, gotcha_widget_class_);
		if (gotcha_widget_.IsValid())
		{
			gotcha_widget_->AddToViewport();
		}
	}
}
