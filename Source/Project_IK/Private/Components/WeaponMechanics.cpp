/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for WeaponMechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Components/WeaponMechanics.h"
#include "AIController.h"
#include "AI/GunnerAIController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Weapons/Gun.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

// Sets default values for this component's properties
UWeaponMechanics::UWeaponMechanics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	head_socket_name_ = TEXT("head_socket");
	gun_socket_name_ = TEXT("rifle_socket");
	owned_cover_key_name_ = TEXT("OwnedCover");
}

void UWeaponMechanics::EquipWeapon()
{
	//Weapon class는 C++에서 생성&Load하지 않는다. Gun들의 BP를 각 Hero/Enemy의  WeaponMechanics BP에서 설정해 줘야 한다.
	weapon_ref_ = Cast<AGun>(GetWorld()->SpawnActor(weapon_class_));
	weapon_ref_->AttachToComponent(character_ref_->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, gun_socket_name_);
}

// Called when the game starts
void UWeaponMechanics::BeginPlay()
{
	Super::BeginPlay();
	character_ref_ = Cast<ACharacter>(GetOwner());
	EquipWeapon();
}

void UWeaponMechanics::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
	GetWorld()->GetTimerManager().ClearTimer(reload_timer_handle_);
	Super::EndPlay(EndPlayReason);
}

void UWeaponMechanics::FireWeapon(AActor* target, float damage)
{
	if(weapon_ref_)
	{
		ACharacter* casted_target = Cast<ACharacter>(target);
		const UBlackboardComponent* blackboard = Cast<AAIController>(casted_target->GetController())->GetBlackboardComponent();
		UObject* cover = blackboard->GetValueAsObject(owned_cover_key_name_);
		if(IsValid(cover))
		{
			if(FMath::RandRange(0, 100) > 50)
			{
				weapon_ref_->FireWeapon(casted_target->GetMesh()->GetSocketLocation(head_socket_name_), damage);
			}
			else
			{
				weapon_ref_->FireWeapon(target->GetActorLocation() - FVector(0, 0, 50), damage);
			}
		}
		else
		{
			weapon_ref_->FireWeapon(target->GetActorLocation(), damage);
		}

		if(auto gunner_controller = Cast<AGunnerAIController>(Cast<APawn>(GetOwner())->Controller))
		{
			gunner_controller->SetFireState(EFireState::WaitingFire);
		}
	}
}

void UWeaponMechanics::WaitNextFire()
{
	if(GetWorld()->GetTimerManager().IsTimerActive(fire_timer_handle_) == false)
	{
		GetWorld()->GetTimerManager().SetTimer(fire_timer_handle_, this, &UWeaponMechanics::FinishFire, weapon_ref_->GetFireInterval());
	}
}

void UWeaponMechanics::FinishFire()
{
	if(auto gunner_controller = Cast<AGunnerAIController>(Cast<APawn>(GetOwner())->Controller))
	{
		gunner_controller->SetFireState(EFireState::BeginFire);
		GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
	}
}
void UWeaponMechanics::Reload()
{
	if(auto gunner_controller = Cast<AGunnerAIController>(Cast<APawn>(GetOwner())->Controller))
	{
		gunner_controller->SetReloadState(EReloadState::WaitingReload);
	}
}

void UWeaponMechanics::WaitReload()
{
	if(GetWorld()->GetTimerManager().IsTimerActive(reload_timer_handle_) == false)
	{
		GetWorld()->GetTimerManager().SetTimer(reload_timer_handle_, this, &UWeaponMechanics::FinishReload, weapon_ref_->GetReloadDuration());
	}
}

void UWeaponMechanics::FinishReload()
{
	//실제 장전 애니메이션이 끝나면 총알을 채워넣는다.
	if(weapon_ref_) weapon_ref_->Reload();
	if(auto gunner_controller = Cast<AGunnerAIController>(Cast<APawn>(GetOwner())->Controller))
	{
		gunner_controller->SetReloadState(EReloadState::BeginReload);

		GetWorld()->GetTimerManager().ClearTimer(reload_timer_handle_);
	}
}

void UWeaponMechanics::OnDestroy()
{
	if(weapon_ref_) weapon_ref_->Destroy();
}

bool UWeaponMechanics::IsMagazineEmpty() const
{
	return weapon_ref_->IsMagazineEmpty();
}

float UWeaponMechanics::GetFireInterval() const
{
	return weapon_ref_->GetFireInterval();
}

float UWeaponMechanics::GetReloadDuration() const
{
	return weapon_ref_->GetReloadDuration();
}

void UWeaponMechanics::SetWeaponOwner(TWeakObjectPtr<AActor> gun_owner)
{
	weapon_ref_->SetGunOwner(gun_owner);
}
