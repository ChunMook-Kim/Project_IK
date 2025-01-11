/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.3.2025
Summary : Source file of user widget class to gotcha.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/GotchaWidget.h"

#include "Kismet/GameplayStatics.h"

#include "WorldSettings/IKGameInstance.h"
#include "Managers/ItemDataManager.h"
#include "Managers/DronePluginManager.h"
#include "Managers/TextureManager.h"
#include "Abilities/ItemInventory.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/GotchaResultWidget.h"

void UGotchaWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (back_space_.IsValid())
	{
		back_space_->OnClicked.AddDynamic(this, &UGotchaWidget::BackSpace);
	}
	if (pull_one_button_.IsValid())
	{
		pull_one_button_->OnClicked.AddDynamic(this, &UGotchaWidget::PullOne);
	}
	if (pull_ten_button_.IsValid())
	{
		pull_ten_button_->OnClicked.AddDynamic(this, &UGotchaWidget::PullTen);
	}
	if (result_widget_class_)
	{
		result_widget_ = WidgetTree->ConstructWidget<UGotchaResultWidget>(result_widget_class_);
		result_widget_->AddToViewport(1);
	}

	tickets_ = 99;
	UpdateGotchaTicketCount();
}

void UGotchaWidget::BackSpace()
{
	// @@ TODO: Go to proper level
	// UGameplayStatics::OpenLevel(GetWorld(), FName("CombatLevel"));
}

void UGotchaWidget::PullOne()
{
	if (tickets_ < 1)
	{
		return;
	}

	SetTickets(tickets_ - 1);
	Gotcha(1);
}

void UGotchaWidget::PullTen()
{
	if (tickets_ < 10)
	{
		return;
	}
	SetTickets(tickets_ - 10);
	Gotcha(10);
}

void UGotchaWidget::SetTickets(int32 tickets)
{
	tickets_ = tickets;
	UpdateGotchaTicketCount();
}

void UGotchaWidget::UpdateGotchaTicketCount()
{
	tickets_count_text_->SetText(FText::FromString(FString::Printf(TEXT("%d"), tickets_)));
}

void UGotchaWidget::Gotcha(int32 pulls)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	const UItemDataManager* item_data_manager = game_instance->GetItemDataManager();
	const UDronePluginManager* drone_plugin_manager = game_instance->GetDronePluginManager();
	const UTextureManager* texture_manager = game_instance->GetTextureManager();
	
	TArray<UTexture2D*> textures;
	// @@ TODO: Expand it from only item to item, DP, manuals, money
	for (int32 i = 0; i < pulls; i++)
	{
		int32 tmp = FMath::RandRange(0, 2);
		FItemData* data_item;
		FDPData data_dp;
		switch (tmp)
		{
		case 0:
			data_item = item_data_manager->GetItemDataRandomly();
			game_instance->GetItemInventory()->AddItem(*data_item);
			textures.Add(data_item->item_icon_);
			break;
		case 1:
			data_dp = drone_plugin_manager->GetDPDataRandomly();
			textures.Add(data_dp.dp_icon_);
			break;
		default:
			textures.Add(texture_manager->GetTexture("currency"));
			break;
		}
	}
	if (pulls <= 1)
	{
		result_widget_->DisplayResult(textures[0]);
	}
	else
	{
		result_widget_->DisplayResults(textures);
	}
}
