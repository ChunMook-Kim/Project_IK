/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for hero base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/HeroBase.h"

#include "Abilities/PassiveMechanics.h"
#include "Abilities/SkillContainer.h"
#include "Components/SphereComponent.h"
#include "Components/WeaponMechanics.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"

AHeroBase::AHeroBase()
{
	skill_container_ = CreateDefaultSubobject<USkillContainer>(TEXT("SkillContainer"));
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
	passive_mechanics_ = CreateDefaultSubobject<UPassiveMechanics>("PassiveMechanics");
	drone_location_ = CreateDefaultSubobject<USphereComponent>("Drone Location");
	drone_location_->SetupAttachment(RootComponent);
}

void AHeroBase::Die()
{
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(casted_mode) casted_mode->RemoveHero(this);
	Super::Die();
}

void AHeroBase::Reload()
{
	weapon_mechanics_->Reload();
	PlayAnimMontage(reload_montage_);
}

void AHeroBase::Fire(AActor* target)
{
	weapon_mechanics_->FireWeapon(target);
	PlayAnimMontage(fire_montage_);
}

void AHeroBase::ActivatePassive()
{
	passive_mechanics_->ActivePassiveSkill();
}

bool AHeroBase::IsPassiveAvailable()
{
	return passive_mechanics_->IsPassiveAvailable();
}

float AHeroBase::GetPassiveHoldTime()
{
	return passive_mechanics_->GetHoldTime();
}
