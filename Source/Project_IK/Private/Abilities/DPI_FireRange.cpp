/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for the DPI fire range buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/DPI_FireRange.h"
#include "Characters/Gunner.h"
#include "Components/CharacterStatComponent.h"

ADPI_FireRange::ADPI_FireRange()
{
	is_periodic_ = false;
	buff_amount_ = 200.f;
}

void ADPI_FireRange::BeginPlay()
{
	Super::BeginPlay();
}

void ADPI_FireRange::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ADPI_FireRange::StartPassiveSkill()
{
	Super::StartPassiveSkill();
	gunner_caster_ = Cast<AGunner>(caster_);
	if(gunner_caster_)
	{
		gunner_caster_->GetCharacterStatComponent()->
		SetFireRange(gunner_caster_->GetCharacterStatComponent()->GetFireRange() + buff_amount_);
		UE_LOG(LogTemp, Warning, TEXT("General Buff Activated, cur fire range: %f"), gunner_caster_->GetCharacterStatComponent()->GetFireRange());
	}
}

void ADPI_FireRange::FinishPassiveSkill()
{
	Super::FinishPassiveSkill();
	gunner_caster_ = Cast<AGunner>(caster_);
	if(gunner_caster_)
	{
		gunner_caster_->GetCharacterStatComponent()->
		SetFireRange(gunner_caster_->GetCharacterStatComponent()->GetFireRange() - buff_amount_);
		UE_LOG(LogTemp, Warning, TEXT("Periodic Buff Activated, cur speed: %f"), gunner_caster_->GetCharacterStatComponent()->GetFireRange());
	}
}
