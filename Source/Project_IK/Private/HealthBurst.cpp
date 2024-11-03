// Fill out your copyright notice in the Description page of Project Settings.


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
