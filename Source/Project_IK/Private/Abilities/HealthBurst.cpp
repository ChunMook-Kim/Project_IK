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
#include "Characters/Gunner.h"

void AHealthBurst::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(gunner_caster_ == nullptr) gunner_caster_ = Cast<AGunner>(caster_);
	gunner_caster_->GetCharacterStatComponent()->SetHitPoint(gunner_caster_->GetCharacterStatComponent()->GetHitPoint() + DeltaSeconds * heal_amount_);
	duration_ -= DeltaSeconds;
	if(duration_ < 0) Destroy();
}
