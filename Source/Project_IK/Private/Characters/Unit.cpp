/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for unit.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Unit.h"

#include "AIController.h"
#include "AI/MeleeAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CharacterStatComponent.h"
#include "Components/CrowdControlComponent.h"
#include "Components/WidgetComponent.h"

#include "UI/HitPointsUI.h"
#include "Components/ObjectPoolComponent.h"
#include "UI/DamageUI.h"

// Sets default values
AUnit::AUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	character_stat_component_ = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("CharacterStatComponent"));
	hp_UI_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP UI"));
	
	hp_UI_->SetWidgetSpace(EWidgetSpace::Screen);
	hp_UI_->SetDrawSize({100, 50});
	hp_UI_->SetupAttachment(RootComponent);

	character_stat_component_->Die.AddDynamic(this, &AUnit::Die);

	cc_component_ = CreateDefaultSubobject<UCrowdControlComponent>(TEXT("CC Component"));

	//UI를 위한 경로가 문자열로 되어있으므로, UI BP의 경로 변경시 같이 변경해야 한다.
	static ConstructorHelpers::FClassFinder<UHitPointsUI> UI_BP(TEXT("/Game/__BluePrints/BP_HitPointsUI"));
	if(UI_BP.Succeeded() && UI_BP.Class != nullptr)
	{
		hp_UI_->SetWidgetClass(UI_BP.Class);
	}

	object_pool_component_ = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("ObjectPool"));
}

const UCharacterStatComponent* AUnit::GetCharacterStat() const
{
	return character_stat_component_;
}

FVector AUnit::GetForwardDir() const
{
	return forward_dir_;
}

void AUnit::SetForwardDir(const FVector& Forward_Dir)
{
	forward_dir_ = Forward_Dir;
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	Cast<UHitPointsUI>(hp_UI_->GetWidget())->BindCharacterStat(character_stat_component_);
}

void AUnit::GetDamage(float damage, TWeakObjectPtr<AActor> attacker)
{
	bool is_damaged = character_stat_component_->GetDamage(damage, attacker);

	ADamageUI* ui = Cast<ADamageUI>(object_pool_component_->SpawnFromPool(GetActorTransformForDamageUI()));
	if (ui)
	{
		if (is_damaged)
		{
			ui->SetDamageAmount(damage);
		}
		else
		{
			ui->SetMissed();
		}
	}
}

void AUnit::Heal(float heal)
{
	character_stat_component_->Heal(heal);

	ADamageUI* ui = Cast<ADamageUI>(object_pool_component_->SpawnFromPool(GetActorTransformForDamageUI()));
	if (ui)
	{
			ui->SetHealAmount(heal);
	}
}

void AUnit::ApplyBuff(FBuff buff)
{
	character_stat_component_->ApplyBuff(buff);
}

bool AUnit::RemoveBuff(FName BuffName)
{
	return character_stat_component_->RemoveBuff(BuffName);
}

void AUnit::ApplyCrowdControl(ECCType cc_type, float duration)
{
	cc_component_->ApplyCrowdControl(cc_type, duration);
}

void AUnit::GetStunned()
{
	GetMesh()->SetMaterial(0, test_stun_material_);
	PlayAnimMontage(stun_montage_);
	Cast<AMeleeAIController>(Controller)->SetStunState(EStunState::WaitingStun);
}

void AUnit::FinishStun()
{
	GetMesh()->SetMaterial(0, original_material);
	Cast<AMeleeAIController>(Controller)->SetStunState(EStunState::BeginStun);
	Cast<AMeleeAIController>(Controller)->SetUnitState(EUnitState::Forwarding);
}

void AUnit::Die()
{
	Destroy();
}

FTransform AUnit::GetActorTransformForDamageUI() const noexcept
{
	// Randomize spawn locations
	FTransform transform = GetActorTransform();
	transform.SetLocation(transform.GetLocation() + FVector(10.f, 0.f, 0.f) + FVector(FMath::RandRange(0.f, 10.f), 0.f, FMath::RandRange(0.f, 10.f)));
	return transform;
}
