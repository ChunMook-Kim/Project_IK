/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.07.2025
Summary : Source file for HUD that used in HeroSelectLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/HeroSelect/IKHeroSelectHUD.h"

#include "UI/MapWidget.h"

void AIKHeroSelectHUD::OpenMapWidget()
{
	map_widget_->SetVisibility(ESlateVisibility::Visible);
}

void AIKHeroSelectHUD::BeginPlay()
{
	if (map_widget_class_)
	{
		map_widget_ = CreateWidget<UMapWidget>(GetWorld(), map_widget_class_);
		if (map_widget_.IsValid())
		{
			map_widget_->AddToViewport();
			map_widget_->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
