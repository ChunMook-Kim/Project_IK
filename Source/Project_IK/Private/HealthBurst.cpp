/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for HealthBurst Passive Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "HealthBurst.h"

#include "CharacterStatComponent.h"
#include "Gunner.h"

void AHealthBurst::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(gunner_caster_ == nullptr) gunner_caster_ = Cast<AGunner>(gunner_caster_);
	gunner_caster_->character_stat_component_->SetHitPoint(gunner_caster_->character_stat_component_->GetHitPoint() - DeltaSeconds * heal_amount_);
	duration_ -= DeltaSeconds;
	if(duration_ < 0) Destroy();
}
