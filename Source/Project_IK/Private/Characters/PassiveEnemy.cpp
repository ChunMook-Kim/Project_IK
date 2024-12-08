/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.08.2024
Summary : Source file for Passive Enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/PassiveEnemy.h"

#include "Abilities/PassiveMechanics.h"

APassiveEnemy::APassiveEnemy()
{
	passive_mechanics_ = CreateDefaultSubobject<UPassiveMechanics>(TEXT("PassiveMechanics"));
}

void APassiveEnemy::Die()
{
	Super::Die();
}

void APassiveEnemy::ActivatePassive()
{
	passive_mechanics_->ActivePassiveSkill();
}

bool APassiveEnemy::IsPassiveAvailable()
{
	return passive_mechanics_->IsPassiveAvailable();
}

float APassiveEnemy::GetPassiveHoldTime()
{
	return passive_mechanics_->GetHoldTime();
}
