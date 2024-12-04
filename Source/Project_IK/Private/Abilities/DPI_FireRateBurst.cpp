/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Source file for the DPI fire rate burst.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/DPI_FireRateBurst.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

ADPI_FireRateBurst::ADPI_FireRateBurst()
{
	is_periodic_ = true;
	cool_time_ = 5.f;
	duration_ = 5.f;
	hold_time_ = 0.f;
	accelerate_amount_ = 2.f;
}

void ADPI_FireRateBurst::BeginPlay()
{
	Super::BeginPlay();
}

void ADPI_FireRateBurst::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(activated_ && left_duration_ <= 0)
	{
		FinishPassiveSkill();
	}
}

void ADPI_FireRateBurst::StartPassiveSkill()
{
	Super::StartPassiveSkill();
	unit_caster_ = Cast<AUnit>(caster_);
	if(unit_caster_)
	{
		unit_caster_->GetCharacterStat()->ApplyBuff(FBuff(ECharacterStatType::AttackSpeed, -1.f / accelerate_amount_, true, duration_));
	}
}

void ADPI_FireRateBurst::FinishPassiveSkill()
{
	Super::FinishPassiveSkill();
}
