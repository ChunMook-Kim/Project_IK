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
	left_time_ = cool_time_;
	left_time_ = duration_;
}

void APassiveSkill::Initialize(AActor* caster)
{
	PrimaryActorTick.bCanEverTick = true;
	caster_ = caster;

	//Scene이 load되고 최초 한번은 패시브 지속 시간, duration을 0으로 하고 스킬을 발동하는 것으로 쿨타임만 돌린다.
	activated_ = true;
	left_duration_ = 0.f;
	left_time_ = cool_time_;
}

// Called when the game starts or when spawned
void APassiveSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

void APassiveSkill::StartPassiveSkill()
{
	left_time_ = cool_time_;
	left_duration_ = duration_;
	activated_ = true;
}

void APassiveSkill::FinishPassiveSkill()
{
	activated_ = false;
}

// Called every frame
void APassiveSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(activated_)
	{
		if(left_duration_ > 0.f)
		{
			left_duration_ -= DeltaTime;
		}
	}
	else
	{
		if(left_time_ > 0.f)
		{
			left_time_ -= DeltaTime;
			UE_LOG(LogTemp, Warning, TEXT("Passive Left Cool Time: %f"), left_time_);
		}
	}
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

bool APassiveSkill::IsActivated() const
{
	return activated_;
}

void APassiveSkill::SetActivated(bool bActivated)
{
	activated_ = bActivated;
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
	return left_time_ <= 0;
}