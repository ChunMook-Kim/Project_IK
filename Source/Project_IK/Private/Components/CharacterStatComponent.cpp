/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.14.2024
Summary : Source file for Character Stat class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Project_IK/Public/Components/CharacterStatComponent.h"

#include "Math/UnrealMathUtility.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Project_IK/Public/WorldSettings/IKGameInstance.h"



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

	if (ik_game_instance)
	{
		FCharacterData* character_data = ik_game_instance->GetCharacterDataManager()->GetCharacterData(static_cast<int32>(character_id_));

		stat_.ability_power_ = character_data->ability_power_;
		stat_.attack_ = character_data->attack_;
		stat_.attack_speed_ = character_data->attack_speed_;
		stat_.hit_point_ = character_data->hit_point_;
		stat_.magazine_ = character_data->magazine_;

		stat_.fire_range_ = character_data->fire_range_;
		stat_.move_speed_ = character_data->move_speed_;
		stat_.sight_range_ = character_data->sight_range_;


		// They are initial data of each attributes. Theoretical oritical limitation will be implemented later
		max_stat_.ability_power_ = stat_.ability_power_;
		max_stat_.attack_ = stat_.attack_;
		max_stat_.attack_speed_ = stat_.attack_speed_;
		max_stat_.hit_point_ = stat_.hit_point_;
		max_stat_.magazine_ = stat_.magazine_;

		max_stat_.fire_range_ = stat_.fire_range_;
		max_stat_.move_speed_ = stat_.move_speed_;
		max_stat_.sight_range_ = stat_.sight_range_;
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
	SetHitPoint(stat_.hit_point_ - DamageAmount);
}

float UCharacterStatComponent::GetAbilityPower() const noexcept
{
	return stat_.ability_power_;
}

float UCharacterStatComponent::GetAttack() const noexcept
{
	return stat_.attack_;
}

float UCharacterStatComponent::GetAttackSpeed() const noexcept
{
	return stat_.attack_speed_;
}

float UCharacterStatComponent::GetHitPoint() const noexcept
{
	return stat_.hit_point_;
}

float UCharacterStatComponent::GetMagazine() const noexcept
{
	return stat_.magazine_;
}

float UCharacterStatComponent::GetFireRange() const noexcept
{
	return stat_.fire_range_;
}

float UCharacterStatComponent::GetMoveSpeed() const noexcept
{
	return stat_.move_speed_;
}

float UCharacterStatComponent::GetSightRange() const noexcept
{
	return stat_.sight_range_;
}

void UCharacterStatComponent::SetAbilityPower(float ability_power) noexcept
{
	stat_.ability_power_ = FMath::Min(ability_power, max_stat_.ability_power_);
}

void UCharacterStatComponent::SetAttack(float attack) noexcept
{
	stat_.attack_ = FMath::Min(attack, max_stat_.attack_);
}

void UCharacterStatComponent::SetAttackSpeed(float attack_speed) noexcept
{
	stat_.attack_speed_ = FMath::Min(attack_speed, max_stat_.attack_speed_);
}

void UCharacterStatComponent::SetHitPoint(float hit_point) noexcept
{
	stat_.hit_point_ = FMath::Min(hit_point, max_stat_.hit_point_);

	OnHPChanged.Broadcast();
	if (stat_.hit_point_ < KINDA_SMALL_NUMBER)
	{
		stat_.hit_point_ = 0.f;
		Die.Broadcast();
	}
}

void UCharacterStatComponent::SetMagazine(float magazine) noexcept
{
	stat_.magazine_ = FMath::Min(magazine, max_stat_.magazine_);
}

void UCharacterStatComponent::SetFireRange(float fire_range) noexcept
{
	stat_.fire_range_ = FMath::Min(fire_range, max_stat_.fire_range_);
}

void UCharacterStatComponent::SetMoveSpeed(float move_speed) noexcept
{
	stat_.move_speed_ = FMath::Min(move_speed, max_stat_.move_speed_);
}

void UCharacterStatComponent::SetSightRange(float sight_range) noexcept
{
	stat_.sight_range_ = FMath::Min(sight_range, max_stat_.sight_range_);
}

float UCharacterStatComponent::GetHPRatio() const noexcept
{
	if (max_stat_.hit_point_ < KINDA_SMALL_NUMBER)
	{
		return 0.f;
	}
	else
	{
		return stat_.hit_point_ / max_stat_.hit_point_;
	}
}

float UCharacterStatComponent::GetMaxHitPoint() const noexcept
{
	return max_stat_.hit_point_;
}

FCharacterData UCharacterStatComponent::GetCharacterData() const noexcept
{
	return stat_;
}

void UCharacterStatComponent::SetCharacterData(const FCharacterData& character_data) noexcept
{
	stat_ = character_data;
}
