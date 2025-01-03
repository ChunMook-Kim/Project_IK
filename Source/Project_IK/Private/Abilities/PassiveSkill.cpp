/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for PassiveSkillBase.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/PassiveSkill.h"

// Sets default values
APassiveSkill::APassiveSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	is_available = true;
	on_cool_down_ = false;
	on_passive_skill_ = false;
}

void APassiveSkill::Initialize(AActor* caster)
{
	PrimaryActorTick.bCanEverTick = true;
	caster_ = caster;
	is_available = true;
	on_cool_down_ = false;
	on_passive_skill_ = false;
}

void APassiveSkill::OnDestroy()
{
	GetWorld()->GetTimerManager().ClearTimer(cool_time_handle_);
	GetWorld()->GetTimerManager().ClearTimer(duration_handle_);
}

// Called when the game starts or when spawned
void APassiveSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

void APassiveSkill::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnDestroy();
	Super::EndPlay(EndPlayReason);
}

void APassiveSkill::StartPassiveSkill()
{
	is_available = false;
	on_cool_down_ = false;
	on_passive_skill_ = true;
	GetWorld()->GetTimerManager().SetTimer(duration_handle_, this, &APassiveSkill::FinishPassiveSkillAndStartCoolDown, duration_);
}

void APassiveSkill::FinishPassiveSkillAndStartCoolDown()
{
	on_cool_down_ = true;
	on_passive_skill_ = false;
	GetWorld()->GetTimerManager().ClearTimer(duration_handle_);
	GetWorld()->GetTimerManager().SetTimer(cool_time_handle_, this, &APassiveSkill::FinishCoolDown, cool_time_);
}

void APassiveSkill::FinishCoolDown()
{
	is_available = true;
	on_cool_down_ = false;
	on_passive_skill_ = false;
	GetWorld()->GetTimerManager().ClearTimer(cool_time_handle_);
}

void APassiveSkill::StartHoldCoolDown()
{
	GetWorld()->GetTimerManager().PauseTimer(cool_time_handle_);
}

void APassiveSkill::FinishHoldCoolDown()
{
	GetWorld()->GetTimerManager().UnPauseTimer(cool_time_handle_);
}

void APassiveSkill::StopPassiveSkill()
{
	if(on_passive_skill_)
	{
		on_passive_skill_ = false;
		on_cool_down_ = true;
		GetWorld()->GetTimerManager().ClearTimer(duration_handle_);
		GetWorld()->GetTimerManager().SetTimer(cool_time_handle_, this, &APassiveSkill::FinishCoolDown, cool_time_);
	}
}

// Called every frame
void APassiveSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float APassiveSkill::GetCoolTime() const
{
	return cool_time_;
}

void APassiveSkill::SetCoolTime(float Cool_Time)
{
	cool_time_ = Cool_Time;
}

float APassiveSkill::GetHoldTime() const
{
	return hold_time_;
}

void APassiveSkill::SetHoldTime(float Hold_Time)
{
	hold_time_ = Hold_Time;
}

float APassiveSkill::GetDuration() const
{
	return duration_;
}

void APassiveSkill::SetDuration(float Duration)
{
	duration_ = Duration;
}

bool APassiveSkill::IsPassiveAvailable() const
{
	return is_available;
}

bool APassiveSkill::IsOnPassiveSkill() const
{
	return on_passive_skill_;
}
