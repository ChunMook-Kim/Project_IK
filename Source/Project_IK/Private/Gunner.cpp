/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.04.2024
Summary : Header file for ForwardDestination Environment Query Context.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

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
	
	hp_UI_->SetWidgetSpace(EWidgetSpace::Screen);
	hp_UI_->SetDrawSize({100, 50});
	hp_UI_->SetupAttachment(RootComponent);
	//UI를 위한 경로가 문자열로 되어있으므로, UI BP의 경로 변경시 같이 변경해야 한다.
	static ConstructorHelpers::FClassFinder<UHitPointsUI> UI_BP(TEXT("/Game/__BluePrints/BP_HitPointsUI"));
	if(UI_BP.Succeeded() && UI_BP.Class != nullptr)
	{
		hp_UI_->SetWidgetClass(UI_BP.Class);
	}
}

// Called when the game starts or when spawned
void AGunner::BeginPlay()
{
	Super::BeginPlay();
	Cast<UHitPointsUI>(hp_UI_->GetWidget())->BindCharacterStat(character_stat_component_);
}

void AGunner::GetDamage(float damage)
{
	character_stat_component_->GetDamage(damage);
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

UCharacterStatComponent* AGunner::GetCharacterStatComponent() const
{
	return character_stat_component_;
}

void AGunner::SetCharacterStatComponent(UCharacterStatComponent* Character_Stat_Component)
{
	character_stat_component_ = Character_Stat_Component;
}

FVector AGunner::GetForwardDir() const
{
	return forward_dir_;
}

void AGunner::SetForwardDir(const FVector& Forward_Dir)
{
	forward_dir_ = Forward_Dir;
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

bool AGunner::IsMegazineEmpty() const
{
	return weapon_mechanics_->IsMegazineEmpty();
}

float AGunner::GetReloadDuration() const
{
	return weapon_mechanics_->GetReloadDuration();
}

float AGunner::GetFireInterval() const
{
	return weapon_mechanics_->GetFireInterval();
}
