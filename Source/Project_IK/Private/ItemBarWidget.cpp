/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.20.2024
Summary : Source file for ItemBarWidget.
					A class that derived by UserWidget displays item and works like an interface.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "ItemBarWidget.h"

#include "IKGameInstance.h"
#include "Components/Button.h"
#include "ItemInventory.h"
#include "IKPlayerController.h"
#include "TargetingComponent.h"
#include "SkillBase.h"

void UItemBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	selected_item_index_ = 0;

	if (item_button_0_)
	{
		item_button_0_->OnClicked.AddDynamic(this, &UItemBarWidget::OnButtonClicked0);
	}
	if (item_button_1_)
	{
		item_button_1_->OnClicked.AddDynamic(this, &UItemBarWidget::OnButtonClicked2);
	}
	if (item_button_2_)
	{
		item_button_2_->OnClicked.AddDynamic(this, &UItemBarWidget::OnButtonClicked2);
	}
	
	if (AIKPlayerController* PC = Cast<AIKPlayerController>(GetOwningPlayer()))
	{
		targeting_component_ = PC->GetTargetingComponent();
		if (targeting_component_)
		{
			targeting_component_->OnTargetDataSelected.AddDynamic(this, &UItemBarWidget::UseItem);
		}
	}

	if (UIKGameInstance* GI = Cast<UIKGameInstance>(GetGameInstance()))
	{
		item_inventory_ = GI->GetItemInventory();
	}
}

void UItemBarWidget::OnButtonClicked0()
{
	if (item_inventory_->GetItem(0))
	{
		selected_item_index_ = 0;
		// @@ TODO: Replace PlayerController to the main camera
		targeting_component_->StartTargeting(GetWorld()->GetFirstPlayerController(), ETargetingMode::Location);
	}
}

void UItemBarWidget::OnButtonClicked1()
{
	if (item_inventory_->GetItem(1))
	{
		selected_item_index_ = 1;
		// @@ TODO: Replace PlayerController to the main camera
		targeting_component_->StartTargeting(GetWorld()->GetFirstPlayerController(), ETargetingMode::Location);
	}
}

void UItemBarWidget::OnButtonClicked2()
{
	if (item_inventory_->GetItem(2))
	{
		selected_item_index_ = 2;
		// @@ TODO: Replace PlayerController to the main camera
		targeting_component_->StartTargeting(GetWorld()->GetFirstPlayerController(), ETargetingMode::Location);
	}
}

void UItemBarWidget::UseItem(const FTargetData& TargetData)
{
	item_inventory_->GetItem(selected_item_index_)->ActivateSkill(TargetData);
}
