/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.04.2024
Summary : Source file for Skill Bar UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/



#include "UI/ButtonBarWidget.h"

#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"
#include "WorldSettings/IKGameModeBase.h"
#include "Abilities/SkillContainer.h"
#include "Components/TargetingComponent.h"
#include "WorldSettings/IKPlayerController.h"
#include "Abilities/ItemInventory.h"
#include "WorldSettings/IKGameInstance.h"

void UButtonBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FindCharacters();

	if (skill_button_0_)
	{
		skill_button_0_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSkillButtonClicked0);
	}
	if (skill_button_1_)
	{
		skill_button_1_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSkillButtonClicked1);
	}
	if (skill_button_2_)
	{
		skill_button_2_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSkillButtonClicked2);
	}
	if (skill_button_3_)
	{
		skill_button_3_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnSkillButtonClicked3);
	}

	if (item_button_0_)
	{
		item_button_0_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnItemButtonClicked0);
	}
	if (item_button_1_)
	{
		item_button_1_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnItemButtonClicked1);
	}
	if (item_button_2_)
	{
		item_button_2_->OnClicked.AddDynamic(this, &UButtonBarWidget::OnItemButtonClicked2);
	}

	if (AIKPlayerController* PC = Cast<AIKPlayerController>(GetOwningPlayer()))
	{
		targeting_component_ = PC->GetTargetingComponent();
		if (targeting_component_)
		{
			targeting_component_->OnTargetDataSelected.AddDynamic(this, &UButtonBarWidget::InvokeSkills);
		}
	}

	if (UIKGameInstance* GI = Cast<UIKGameInstance>(GetGameInstance()))
	{
		item_inventory_ = GI->GetItemInventory();
	}

	caster_ = -1;
	selected_item_index_ = -1;
}

void UButtonBarWidget::OnSkillButtonClicked0()
{
	caster_ = 0;
	selected_item_index_ = -1;
	if (targeting_component_)
	{
		targeting_component_->StartSkillTargeting(characters_[caster_], ETargetingMode::Direction, 1000, 90);
	}
}

void UButtonBarWidget::OnSkillButtonClicked1()
{
	caster_ = 1;
	selected_item_index_ = -1;
	if (targeting_component_)
	{
		targeting_component_->StartSkillTargeting(characters_[caster_], ETargetingMode::Location);
	}
}

void UButtonBarWidget::OnSkillButtonClicked2()
{
	caster_ = 2;
	selected_item_index_ = -1;
	if (targeting_component_)
	{
		targeting_component_->StartSkillTargeting(characters_[caster_], ETargetingMode::Location);
	}
}

void UButtonBarWidget::OnSkillButtonClicked3()
{
	caster_ = 3;
	selected_item_index_ = -1;
	if (targeting_component_)
	{
		targeting_component_->StartSkillTargeting(characters_[caster_], ETargetingMode::Location);
	}
}

void UButtonBarWidget::OnItemButtonClicked0()
{
	if (item_inventory_->GetItem(0))
	{
		caster_ = -1;
		selected_item_index_ = 0;
		targeting_component_->StartItemTargeting(ETargetingMode::Actor);
	}
}

void UButtonBarWidget::OnItemButtonClicked1()
{
	if (item_inventory_->GetItem(1))
	{
		caster_ = -1;
		selected_item_index_ = 1;
		targeting_component_->StartItemTargeting(ETargetingMode::Location);
	}
}

void UButtonBarWidget::OnItemButtonClicked2()
{
	if (item_inventory_->GetItem(2))
	{
		caster_ = -1;
		selected_item_index_ = 2;
		targeting_component_->StartItemTargeting(ETargetingMode::Location);
	}
}

void UButtonBarWidget::InvokeSkills(const FTargetData& TargetData)
{
	if (caster_ < 0)
	{
		item_inventory_->GetItem(selected_item_index_)->ActivateSkill(TargetData);
	}
	else
	{
		skill_containers_[caster_]->InvokeSkills(TargetData);
	}
}

void UButtonBarWidget::FindCharacters()
{
	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (game_mode)
	{
		characters_ = game_mode->GetHeroContainers();

		for (AActor* actor : characters_)
		{
			if (actor)
			{
				if (auto skill_container = actor->FindComponentByClass<USkillContainer>();
					skill_container)
				{
					skill_containers_.Add(skill_container);
				}
			}
		}
	}
}
