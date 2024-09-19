/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.14.2024
Summary : Source file for Character Stat class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "CharacterStatComponent.h"

// Sets default values
UCharacterStatComponent::UCharacterStatComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
}

// Called when the game starts or when spawned
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void UCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunctionoverride)
{
	Super::TickComponent(DELTA, TickType, ThisTickFunctionoverride);
}

float UCharacterStatComponent::GetAbilityPower() noexcept
{
	return ability_power_;
}

float UCharacterStatComponent::GetAttack() noexcept
{
	return attack_;
}

float UCharacterStatComponent::GetAttackSpeed() noexcept
{
	return attack_speed_;
}

float UCharacterStatComponent::GetHitPoint() noexcept
{
	return hit_point_;
}

float UCharacterStatComponent::GetMagazine() noexcept
{
	return magazine_;
}

float UCharacterStatComponent::GetFireRange() noexcept
{
	return fire_range_;
}

float UCharacterStatComponent::GetMoveSpeed() noexcept
{
	return move_speed_;
}

float UCharacterStatComponent::GetSightRange() noexcept
{
	return sight_range_;
}

void UCharacterStatComponent::SetAbilityPower(float ability_power) noexcept
{
	ability_power_ = ability_power;
}

void UCharacterStatComponent::SetAttack(float attack) noexcept
{
	attack_ = attack;
}

void UCharacterStatComponent::SetAttackSpeed(float attack_speed) noexcept
{
	attack_speed_ = attack_speed;
}

void UCharacterStatComponent::SetHitPoint(float hit_point) noexcept
{
	hit_point_ = hit_point;
}

void UCharacterStatComponent::SetMagazine(float magazine) noexcept
{
	magazine_ = magazine;
}

void UCharacterStatComponent::SetFireRange(float fire_range) noexcept
{
	fire_range_ = fire_range;
}

void UCharacterStatComponent::SetMoveSpeed(float move_speed) noexcept
{
	move_speed_ = move_speed;
}

void UCharacterStatComponent::SetSightRange(float sight_range) noexcept
{
	sight_range_ = sight_range;
}

