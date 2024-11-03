// Fill out your copyright notice in the Description page of Project Settings.


#include "Gunner.h"
#include "GunnerAIController.h"
#include "CharacterStatComponent.h"
#include "SkillContainer.h"
#include "WeaponMechanics.h"
#include "HitPointsUI.h"
#include "Components/WidgetComponent.h"
// Sets default values
AGunner::AGunner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	character_stat_component_ = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CharacterStatComponent"));
	skill_container_ = CreateDefaultSubobject<USkillContainer>(TEXT("SkillContainer"));
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
	hp_UI_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP UI"));
}

// Called when the game starts or when spawned
void AGunner::BeginPlay()
{
	Super::BeginPlay();
	Cast<UHitPointsUI>(hp_UI_->GetWidget())->BindCharacterStat(character_stat_component_);
}

// Called every frame
void AGunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunner::GetDamage(int damage_amount)
{
	character_stat_component_->GetDamage(damage_amount);
}

// Called to bind functionality to input
void AGunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGunner::OnDie()
{
	weapon_mechanics_->OnDestroy();
	Cast<AGunnerAIController>(GetController())->OnDie();
	Destroy();
}

void AGunner::Fire(AActor* target)
{
	weapon_mechanics_->FireWeapon(target);
	PlayAnimMontage(fire_montage_);
}

void AGunner::Reload()
{
	weapon_mechanics_->Reload();
	PlayAnimMontage(reload_montage_);
}


