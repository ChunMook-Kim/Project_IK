/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.08.2025
Summary : Source file of widget that choose whether keep the item or discard.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/ItemKeepOrDiscardWidget.h"

#include "Blueprint/WidgetTree.h"
#include "UI/CheckboxButtonWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Button.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/TextureManager.h"

bool UItemKeepOrDiscardWidget::Initialize()
{
	Super::Initialize();
	return true;
}

void UItemKeepOrDiscardWidget::NativeConstruct()
{
	Super::NativeConstruct();
	const UTextureManager* texture_manager = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetTextureManager();
	UCheckboxButtonWidget* cb = WidgetTree->ConstructWidget<UCheckboxButtonWidget>(check_box_button_class_);
	cb->SetButtonTexture(texture_manager->GetTexture("currency"));
	if (cb)
	{
		UHorizontalBoxSlot* cb_slot = candidates_item_container_->AddChildToHorizontalBox(cb);
		if (cb_slot)
		{
			cb_slot->SetPadding(FMargin(64.f, 0.f));
		}

		candidates_items_.Add(cb);
	}

	UCheckboxButtonWidget* cb2 = WidgetTree->ConstructWidget<UCheckboxButtonWidget>(check_box_button_class_);
	cb2->SetButtonTexture(texture_manager->GetTexture("currency"));
	cb2->ToggleChecked();
	if (cb2)
	{
		UHorizontalBoxSlot* cb_slot2 = inventory_item_container_->AddChildToHorizontalBox(cb2);
		if (cb_slot2)
		{
			cb_slot2->SetPadding(FMargin(64.f, 0.f));
		}

		inventory_items_.Add(cb2);
	}

	confirm_button_->OnClicked.AddDynamic(this, &UItemKeepOrDiscardWidget::OnConfirmButtonClicked);
}

void UItemKeepOrDiscardWidget::OnConfirmButtonClicked()
{
	inventory_items_[0]->ToggleChecked();
}
