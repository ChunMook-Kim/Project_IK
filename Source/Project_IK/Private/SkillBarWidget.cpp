/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.04.2024
Summary : Source file for Skill Bar UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/



#include "SkillBarWidget.h"

#include "Kismet/GameplayStatics.h"

#include "SkillContainer.h"
#include "TargetingComponent.h"
#include "IKPlayerController.h"

void USkillBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FindCharacters();

	if (skill_button_0_)
	{
		skill_button_0_->OnClicked.AddDynamic(this, &USkillBarWidget::OnButtonClicked0);
	}
	if (skill_button_1_)
	{
		skill_button_1_->OnClicked.AddDynamic(this, &USkillBarWidget::OnButtonClicked1);
	}
	if (skill_button_2_)
	{
		skill_button_2_->OnClicked.AddDynamic(this, &USkillBarWidget::OnButtonClicked2);
	}
	if (skill_button_3_)
	{
		skill_button_3_->OnClicked.AddDynamic(this, &USkillBarWidget::OnButtonClicked3);
	}

	if (AIKPlayerController* PC = Cast<AIKPlayerController>(GetOwningPlayer()))
	{
		targeting_component_ = PC->GetTargetingComponent();
		if (targeting_component_)
		{
			targeting_component_->OnTargetDataSelected.AddDynamic(this, &USkillBarWidget::InvokeSkills);
		}
	}
}

void USkillBarWidget::OnButtonClicked0()
{
	caster_ = 0;
	if (targeting_component_)
	{
		targeting_component_->StartTargeting(characters_[caster_], ETargetingMode::Location);
	}
}

void USkillBarWidget::OnButtonClicked1()
{
	caster_ = 1;
	if (targeting_component_)
	{
		targeting_component_->StartTargeting(characters_[caster_], ETargetingMode::Location);
	}
}

void USkillBarWidget::OnButtonClicked2()
{
	caster_ = 2;
	if (targeting_component_)
	{
		targeting_component_->StartTargeting(characters_[caster_], ETargetingMode::Location);
	}
}

void USkillBarWidget::OnButtonClicked3()
{
	caster_ = 3;
	if (targeting_component_)
	{
		targeting_component_->StartTargeting(characters_[caster_], ETargetingMode::Location);
	}
}

void USkillBarWidget::InvokeSkills(const FTargetData& TargetData)
{
	skill_containers_[caster_]->InvokeSkills(TargetData);
}

void USkillBarWidget::FindCharacters()
{
	TArray<AActor*> all_actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), all_actors);

	for (AActor* actor : all_actors)
	{
		if (actor)
		{
			if (auto skill_container = actor->FindComponentByClass<USkillContainer>();
				skill_container)
			{
				characters_.Add(actor);
				skill_containers_.Add(skill_container);
			}
		}
	}
}
