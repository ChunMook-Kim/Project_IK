/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Source file for Skill base class.
					It will be used like a pure virtual class. A skill class will derived it.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/SkillBase.h"

#include "Components/EnergySystemComponent.h"
#include "WorldSettings/IKGameState.h"



USkillBase::USkillBase()
	: Super::UObject(), cost_(0.f)
{
}

USkillBase::USkillBase(float cost)
	: Super::UObject(), cost_(cost)
{
}

bool USkillBase::SpendCost()
{
	AIKGameState* game_state = GetWorld()->GetGameState<AIKGameState>();
	if (game_state && game_state->energy_system_)
	{
		return game_state->energy_system_->UseEnergy(cost_);
	}

	return false;
}
