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

	if (skill_button_)
	{
		skill_button_->OnClicked.AddDynamic(this, &USkillBarWidget::OnButtonClicked);
	}

	if (AIKPlayerController* PC = Cast<AIKPlayerController>(GetOwningPlayer()))
	{
		targeting_component_ = PC->GetTargetingComponent();
		if (targeting_component_)
		{
			targeting_component_->OnTargetDataSelected.AddDynamic(this, &USkillBarWidget::TMP);
		}
	}
}

void USkillBarWidget::OnButtonClicked()
{
	if (targeting_component_)
	{
		targeting_component_->StartTargeting(ETargetingMode::None);
	}
}

void USkillBarWidget::TMP(const FTargetData& TargetData)
{
	UE_LOG(LogTemp, Display, TEXT("TMP is called"));

	TArray<AActor*> all_actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), all_actors);

	TArray<USkillContainer*> skill_containers;

	for (AActor* actor : all_actors)
	{
		if (actor)
		{
			if (auto skill_container= actor->FindComponentByClass<USkillContainer>();
				skill_container)
			{
				skill_containers.Add(skill_container);
			}
		}
	}

	for (USkillContainer* skill_container : skill_containers)
	{
		skill_container->InvokeSkills();
	}
}
