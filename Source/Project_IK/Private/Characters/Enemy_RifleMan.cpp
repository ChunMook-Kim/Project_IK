/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for rifle man enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Enemy_RifleMan.h"
#include "Components/WeaponMechanics.h"

AEnemy_RifleMan::AEnemy_RifleMan()
{
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
}

void AEnemy_RifleMan::Reload()
{
	weapon_mechanics_->Reload();
	PlayAnimMontage(reload_montage_);
}

void AEnemy_RifleMan::Fire(AActor* target)
{
	weapon_mechanics_->FireWeapon(target);
	PlayAnimMontage(fire_montage_);
}