/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.26.2024
Summary : Source file for skill containers.
					An actor component class to contain skills.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/SkillContainer.h"

// Sets default values for this component's properties
USkillContainer::USkillContainer()
	: Super::UActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
}

void USkillContainer::InitializeComponent()
{
	if (skill_class_)
	{
		skill_ = NewObject<USkillBase>(this, skill_class_);
	}
}

void USkillContainer::InvokeSkills(const FTargetData& TargetData)
{
	if (skill_)
	{
		skill_->ActivateSkill(TargetData);
	}
}


// Called when the game starts
void USkillContainer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
