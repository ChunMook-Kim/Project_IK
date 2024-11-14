/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Gunner PassiveSkill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Characters/PassiveSkillGunner.h"
#include "Abilities/PassiveMechanics.h"

APassiveSkillGunner::APassiveSkillGunner()
{
	passive_mechanics_ = CreateDefaultSubobject<UPassiveMechanics>("PassiveMechanics");
}

bool APassiveSkillGunner::IsPassiveAvailable() const
{
	return passive_mechanics_->IsPassiveAvailable();
}

void APassiveSkillGunner::ActivatePassive()
{
	passive_mechanics_->ActivePassiveSkill();
}
float APassiveSkillGunner::GetPassiveHoldTime() const
{
	return passive_mechanics_->GetHoldTime();
}