/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Source file for the DPI fire rate burst.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/DPI_FireRateBurst.h"
#include "Characters/Gunner.h"
#include "Components/CharacterStatComponent.h"

ADPI_FireRateBurst::ADPI_FireRateBurst()
{
	cool_time_ = 5.f;
	duration_ = 2.f;
	hold_time_ = 0.f;
	accelerate_amount_ = 2.f;
}

void ADPI_FireRateBurst::BeginPlay()
{
	Super::BeginPlay();
	gunner_caster_ = Cast<AGunner>(caster_);
}

void ADPI_FireRateBurst::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(activated_ && left_duration_ <= 0)
	{
		FinishPassiveSkill();
		UE_LOG(LogTemp, Warning, TEXT("Buff Finished"));
	}
}

void ADPI_FireRateBurst::StartPassiveSkill()
{
	Super::StartPassiveSkill();
	UE_LOG(LogTemp, Warning, TEXT("Buff Activated"));
	gunner_caster_ = Cast<AGunner>(caster_);
	if(gunner_caster_)
	{
		gunner_caster_->GetCharacterStatComponent()->
		SetAttackSpeed(gunner_caster_->GetCharacterStatComponent()->GetAttackSpeed() / accelerate_amount_);
	}
}

void ADPI_FireRateBurst::FinishPassiveSkill()
{
	Super::FinishPassiveSkill();
	gunner_caster_ = Cast<AGunner>(caster_);
	if(gunner_caster_)
	{
		gunner_caster_->GetCharacterStatComponent()->
		SetAttackSpeed(gunner_caster_->GetCharacterStatComponent()->GetAttackSpeed() * accelerate_amount_);
	}
}
