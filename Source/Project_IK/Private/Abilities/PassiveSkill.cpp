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
}

void APassiveSkill::Initialize(AActor* caster)
{
	PrimaryActorTick.bCanEverTick = true;
	caster_ = caster;
}

// Called when the game starts or when spawned
void APassiveSkill::BeginPlay()
{
	Super::BeginPlay();
	
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
	cool_time_ = Cool_Time = Cool_Time;
}

float APassiveSkill::GetHoldTime() const
{
	return hold_time_;
}

void APassiveSkill::SetHoldTime(float Hold_Time)
{
	hold_time_ = Hold_Time = Hold_Time;
}

float APassiveSkill::GetDuration() const
{
	return duration_;
}

void APassiveSkill::SetDuration(float Duration)
{
	duration_ = Duration;
}


