/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.08.2024
Summary : Source file for Passive Gunner Enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/PassiveGunnerEnemy.h"
#include "Components/CharacterStatComponent.h"
#include "Components/WeaponMechanics.h"

APassiveGunnerEnemy::APassiveGunnerEnemy()
{
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
}

void APassiveGunnerEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	weapon_mechanics_->SetWeaponOwner(this);		
}

void APassiveGunnerEnemy::Die()
{
	weapon_mechanics_->OnDestroy();
	
	Super::Die();
}

void APassiveGunnerEnemy::Reload()
{
	weapon_mechanics_->Reload();
	PlayAnimMontage(reload_montage_);
}

void APassiveGunnerEnemy::Fire(AActor* target)
{
	weapon_mechanics_->FireWeapon(target, GetCharacterStat()->GetAttack());
	PlayAnimMontage(fire_montage_);
}

bool APassiveGunnerEnemy::IsMagazineEmpty() const
{
	return weapon_mechanics_->IsMagazineEmpty();
}

float APassiveGunnerEnemy::GetFireInterval() const
{
	return weapon_mechanics_->GetFireInterval() * character_stat_component_->GetAttackSpeed();
}

float APassiveGunnerEnemy::GetReloadDuration() const
{
	return weapon_mechanics_->GetReloadDuration();
}
