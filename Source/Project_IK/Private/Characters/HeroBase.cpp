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
#include "AI/GunnerAIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/CharacterStatComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WeaponMechanics.h"
#include "Components/CharacterStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/Drone.h"
#include "WorldSettings/IKGameModeBase.h"
#include "Weapons/Drone.h"

AHeroBase::AHeroBase()
{
	skill_container_ = CreateDefaultSubobject<USkillContainer>(TEXT("SkillContainer"));
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
	passive_mechanics_ = CreateDefaultSubobject<UPassiveMechanics>(TEXT("PassiveMechanics"));
	drone_location_ = CreateDefaultSubobject<USphereComponent>("Drone Location");

	drone_location_->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("HeroPreset"));
	
	drone_location_->SetupAttachment(RootComponent);
	drone_location_->SetRelativeLocation({0, -49, 90});

	forward_dir_ = {1,0, 0};
}

void AHeroBase::BeginPlay()
{
	Super::BeginPlay();

	drone_ = GetWorld()->SpawnActor<ADrone>(drone_bp_class_, drone_location_->GetComponentTransform());
	weapon_mechanics_->SetWeaponOwner(this);		

	if(drone_ == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed To create Drone!"));
	}
	else
	{
		Cast<ADrone>(drone_)->Initialize(this	);
		drone_->AttachToComponent(drone_location_, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void AHeroBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_);
	Super::EndPlay(EndPlayReason);
}

void AHeroBase::Initialize()
{
	if(drone_)
	{
		drone_->SetPlugins(character_stat_component_->GetPeriodicDP(), character_stat_component_->GetGeneralDP());
	}
}

void AHeroBase::Die()
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_);
	weapon_mechanics_->OnDestroy();
	Cast<AGunnerAIController>(GetController())->OnDie();
	if(auto casted_drone = Cast<ADrone>(drone_))
	{
		casted_drone->Die();
	}
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(casted_mode) casted_mode->RemoveHero(this);
	Super::Die();
}

void AHeroBase::Reload()
{	UE_LOG(LogTemp, Warning, TEXT("Reloaded"));
	PlayAnimMontage(reload_montage_);
	weapon_mechanics_->Reload();
}

void AHeroBase::WaitForDuration()
{
	weapon_mechanics_->WaitReload();
}

void AHeroBase::FinishReload()
{
	weapon_mechanics_->FinishReload();
}

void AHeroBase::StartFire(AActor* target)
{
	float gun_as = 1.f / weapon_mechanics_->GetFireInterval();
	float unit_as = GetCharacterStat()->GetAttackSpeed();
	float total_as = gun_as / unit_as;
	if(GetWorld()->GetTimerManager().IsTimerActive(fire_timer_) == false && target)
	{
		FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &AHeroBase::OnFire, target);
		GetWorld()->GetTimerManager().SetTimer(fire_timer_, fire_del, total_as, true, 0); 
	}
}

void AHeroBase::OnFire(AActor* target)
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

void AHeroBase::FinishFire()
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_);
}

bool AHeroBase::IsMagazineEmpty() const
{
	return weapon_mechanics_->IsMagazineEmpty();
}

float AHeroBase::GetFireInterval() const
{
	return weapon_mechanics_->GetFireInterval() * character_stat_component_->GetAttackSpeed();
}

float AHeroBase::GetReloadDuration() const
{
	return weapon_mechanics_->GetReloadDuration();
}

void AHeroBase::ActivatePassive()
{
	passive_mechanics_->ActivatePassiveSkill();
}

void AHeroBase::WaitForHoldTime()
{
	passive_mechanics_->WaitingHoldTime();
}

void AHeroBase::FinishPassive()
{
}

bool AHeroBase::IsPassiveAvailable()
{
	return passive_mechanics_->IsPassiveAvailable();
}

float AHeroBase::GetPassiveHoldTime()
{
	return passive_mechanics_->GetHoldTime();
}

void AHeroBase::GetStunned(float stun_duration)
{
	Super::GetStunned(stun_duration);
}

void AHeroBase::OnStunned()
{
	Super::OnStunned();
	//Hero는 Stun될 시, 사격과 패시브를 멈춰야 한다.
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_);
}
