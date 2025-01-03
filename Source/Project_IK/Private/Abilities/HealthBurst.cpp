/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for HealthBurst Passive Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/HealthBurst.h"

#include "Components/CharacterStatComponent.h"
#include "Characters/Unit.h"

AHealthBurst::AHealthBurst()
{
	duration_ = 2.f;
	cool_time_ = 5.f;
}

void AHealthBurst::BeginPlay()
{
	Super::BeginPlay();
}

void AHealthBurst::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(on_passive_skill_)
	{
		unit_caster_ = Cast<AUnit>(caster_);
		if(unit_caster_)
		{
			unit_caster_->Heal(DeltaSeconds * heal_amount_);
		}
	}
}
