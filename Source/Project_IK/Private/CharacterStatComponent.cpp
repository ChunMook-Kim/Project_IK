/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.14.2024
Summary : Source file for Character Stat class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Project_IK/Public/CharacterStatComponent.h"

#include "Math/UnrealMathUtility.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Project_IK/Public/IKGameInstance.h"



// Sets default values
UCharacterStatComponent::UCharacterStatComponent()
	: character_id_(ECharacterID::Gunner)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
}

void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	auto ik_game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(ik_game_instance)
	{
	FCharacterData* character_data = ik_game_instance->GetCharacterData(static_cast<int32>(character_id_));

	ability_power_ = character_data->ability_power_;
	attack_ = character_data->attack_;
	attack_speed_ = character_data->attack_speed_;
	hit_point_ = character_data->hit_point_;
	magazine_ = character_data->magazine_;

	fire_range_ = character_data->fire_range_;
	move_speed_ = character_data->move_speed_;
	sight_range_ = character_data->sight_range_;


	// They are initial data of each attributes. Theoretical oritical limitation will be implemented later
	max_ability_power_ = ability_power_;
	max_attack_ = attack_;
	max_attack_speed_ = attack_speed_;
	max_hit_point_ = hit_point_;
	max_magazine_ = magazine_;

	max_fire_range_ = fire_range_;
	max_move_speed_ = move_speed_;
	max_sight_range_ = sight_range_;
	}
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

void UCharacterStatComponent::GetDamage(float DamageAmount)
{
	SetHitPoint(hit_point_ - DamageAmount);
}

float UCharacterStatComponent::GetAbilityPower() const noexcept
{
	return ability_power_;
}

float UCharacterStatComponent::GetAttack() const noexcept
{
	return attack_;
}

float UCharacterStatComponent::GetAttackSpeed() const noexcept
{
	return attack_speed_;
}

float UCharacterStatComponent::GetHitPoint() const noexcept
{
	return hit_point_;
}

float UCharacterStatComponent::GetMagazine() const noexcept
{
	return magazine_;
}

float UCharacterStatComponent::GetFireRange() const noexcept
{
	return fire_range_;
}

float UCharacterStatComponent::GetMoveSpeed() const noexcept
{
	return move_speed_;
}

float UCharacterStatComponent::GetSightRange() const noexcept
{
	return sight_range_;
}

void UCharacterStatComponent::SetAbilityPower(float ability_power) noexcept
{
	ability_power_ = FMath::Min(ability_power, max_ability_power_);
}

void UCharacterStatComponent::SetAttack(float attack) noexcept
{
	attack_ = FMath::Min(attack, max_attack_);
}

void UCharacterStatComponent::SetAttackSpeed(float attack_speed) noexcept
{
	attack_speed_ = FMath::Min(attack_speed, max_attack_speed_);
}

void UCharacterStatComponent::SetHitPoint(float hit_point) noexcept
{
	hit_point_ = FMath::Min(hit_point, max_hit_point_);

	OnHPChanged.Broadcast();
	if (hit_point_ < KINDA_SMALL_NUMBER)
	{
		hit_point_ = 0.f;
		Die.Broadcast();
	}
}

void UCharacterStatComponent::SetMagazine(float magazine) noexcept
{
	magazine_ = FMath::Min(magazine, max_magazine_);
}

void UCharacterStatComponent::SetFireRange(float fire_range) noexcept
{
	fire_range_ = FMath::Min(fire_range, max_fire_range_);
}

void UCharacterStatComponent::SetMoveSpeed(float move_speed) noexcept
{
	move_speed_ = FMath::Min(move_speed, max_move_speed_);
}

void UCharacterStatComponent::SetSightRange(float sight_range) noexcept
{
	sight_range_ = FMath::Min(sight_range, max_sight_range_);
}

float UCharacterStatComponent::GetHPRatio() const noexcept
{
	if (max_hit_point_ < KINDA_SMALL_NUMBER)
	{
		return 0.f;
	}
	else
	{
		return hit_point_ / max_hit_point_;
	}
}