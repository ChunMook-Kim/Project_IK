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
#include "Kismet/GameplayStatics.h"
#include "Weapons/Drone.h"
#include "WorldSettings/IKGameModeBase.h"

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
	weapon_mechanics_->SetWeaponOwner(this);		
	drone_ = GetWorld()->SpawnActor<AActor>(drone_bp_class_, drone_location_->GetComponentTransform());
	
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

void AHeroBase::Die()
{
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
{
	weapon_mechanics_->Reload();
	PlayAnimMontage(reload_montage_);
}

void AHeroBase::Fire(AActor* target)
{
	weapon_mechanics_->FireWeapon(target, GetCharacterStat()->GetAttack());
	PlayAnimMontage(fire_montage_);
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
