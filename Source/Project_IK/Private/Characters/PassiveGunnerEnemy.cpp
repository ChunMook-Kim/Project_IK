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

void APassiveGunnerEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_);
	Super::EndPlay(EndPlayReason);
}

void APassiveGunnerEnemy::Die()
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_);
	weapon_mechanics_->OnDestroy();
	
	Super::Die();
}

void APassiveGunnerEnemy::Reload()
{
	weapon_mechanics_->Reload();
	PlayAnimMontage(reload_montage_);
}

void APassiveGunnerEnemy::WaitForDuration()
{
	weapon_mechanics_->WaitReload();
}

void APassiveGunnerEnemy::FinishReload()
{
	weapon_mechanics_->FinishReload();
}

void APassiveGunnerEnemy::StartFire(AActor* target)
{
	float gun_as = 1.f / weapon_mechanics_->GetFireInterval();
	float unit_as = GetCharacterStat()->GetAttackSpeed();
	float total_as = gun_as / unit_as;
	if(GetWorld()->GetTimerManager().IsTimerActive(fire_timer_) == false)
	{
		FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &APassiveGunnerEnemy::OnFire, target);
		GetWorld()->GetTimerManager().SetTimer(fire_timer_, fire_del, total_as, true, 0); 
	}
}

void APassiveGunnerEnemy::OnFire(AActor* target)
{
	if(IsValid(target))
	{
		weapon_mechanics_->FireWeapon(target, GetCharacterStat()->GetAttack());
		PlayAnimMontage(fire_montage_);
		if(weapon_mechanics_->IsMagazineEmpty())
		{
			GetWorld()->GetTimerManager().ClearTimer(fire_timer_);
		}
	}
}

void APassiveGunnerEnemy::FinishFire()
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_);
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

void APassiveGunnerEnemy::OnStunned()
{
	Super::OnStunned();
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_);
}
