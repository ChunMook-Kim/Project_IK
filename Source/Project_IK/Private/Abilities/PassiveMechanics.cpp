/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Passive Mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/PassiveMechanics.h"
#include "Abilities/PassiveSkill.h"

// Sets default values for this component's properties
UPassiveMechanics::UPassiveMechanics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPassiveMechanics::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UPassiveMechanics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (is_activated_)
	{
		duration_ -= DeltaTime;
		if(duration_ <= 0) cool_down_ -= DeltaTime;
		if(cool_down_ <= 0) is_activated_ = false;
	}
}

void UPassiveMechanics::ActivePassiveSkill()
{
	//TODO: 동적 생성이 아닌, 한번 생성하고 초기화 하는 방식으로 최적화 가능.
	auto spawned_skill = Cast<APassiveSkill>(GetWorld()->SpawnActor(passive_class_));
	spawned_skill->Initialize(GetOwner());
	cool_down_ = spawned_skill->GetCoolTime();
	duration_ = spawned_skill->GetDuration();
	hold_time_ = spawned_skill->GetHoldTime();
	is_activated_ = true;
}

bool UPassiveMechanics::IsPassiveAvailable() const
{
	return is_activated_ == false;
}

float UPassiveMechanics::GetHoldTime() const
{
	return hold_time_;
}
