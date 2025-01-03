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
#include "Abilities/ItemInventory.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UGotchaWidget::NativeConstruct()
{
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
	
	// @@ TODO: Expand it from only item to item, DP, manuals, money
	for (int32 i = 0; i < pulls; i++)
	{
		game_instance->GetItemInventory()->AddItem(*item_data_manager->GetItemDataRandomly());
	}
}
