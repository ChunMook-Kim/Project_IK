/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for rifle man enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Enemy_RifleMan.h"

#include "Components/CharacterStatComponent.h"
#include "Components/WeaponMechanics.h"

AEnemy_RifleMan::AEnemy_RifleMan()
{
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
}

void AEnemy_RifleMan::Die()
{
	weapon_mechanics_->OnDestroy();
	Super::Die();
}

void AEnemy_RifleMan::Reload()
{
	weapon_mechanics_->Reload();
	PlayAnimMontage(reload_montage_);
}

void AEnemy_RifleMan::WaitForDuration()
{
	weapon_mechanics_->WaitReload();
}

void AEnemy_RifleMan::FinishReload()
{
	weapon_mechanics_->FinishReload();
}

void AEnemy_RifleMan::Fire(AActor* target)
{
	weapon_mechanics_->FireWeapon(target, character_stat_component_->GetAttack());
	PlayAnimMontage(fire_montage_);
}

void AEnemy_RifleMan::WaitNextFire()
{
	weapon_mechanics_->WaitNextFire();
}

void AEnemy_RifleMan::FinishFire()
{
	weapon_mechanics_->FinishFire();
}

bool AEnemy_RifleMan::IsMagazineEmpty() const
{
	return weapon_mechanics_->IsMagazineEmpty();
}

float AEnemy_RifleMan::GetFireInterval() const
{
	return weapon_mechanics_->GetFireInterval() * character_stat_component_->GetAttackSpeed();
}

float AEnemy_RifleMan::GetReloadDuration() const
{
	return weapon_mechanics_->GetReloadDuration();
}
