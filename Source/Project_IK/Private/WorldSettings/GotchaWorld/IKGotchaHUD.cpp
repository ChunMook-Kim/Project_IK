/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.28.2024
Summary : Source file of HUD for Gotcha level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "WorldSettings/GotchaWorld/IKGotchaHUD.h"

#include "Blueprint/UserWidget.h"

// @@ TODO: remove it
#include "UI/ItemKeepOrDiscardWidget.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/ItemDataManager.h"

void AIKGotchaHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();

	if (widget_class_)
	{
		widget_ = CreateWidget<UUserWidget>(world, widget_class_);
		if (widget_.IsValid())
		{
			widget_->AddToViewport();
			UItemKeepOrDiscardWidget* item_widget = Cast<UItemKeepOrDiscardWidget>(widget_);
			if (item_widget)
			{
				UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
				if (game_instance)
				{
					const UItemDataManager* item_manager = game_instance->GetItemDataManager();
					TArray<FItemData*> inventory_items;
					for (int32 i = 0; i < 3; i++)
					{
						inventory_items.Add(item_manager->GetItemDataRandomly());
					}
					TArray<FItemData*> candidates_items;
					for (int32 i = 0; i < 7; i++)
					{
						candidates_items.Add(item_manager->GetItemDataRandomly());
					}
					item_widget->UpdateItems(inventory_items, candidates_items);
				}
			}
		}
	}

}
