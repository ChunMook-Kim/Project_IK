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
#include "WorldSettings/IKGameModeBase.h"

#include "UI/DamageUI.h"


// Sets default values
UCharacterStatComponent::UCharacterStatComponent()
	: character_id_(ECharacterID::Gunner), max_hit_points_(0.f)
{
	PrimaryComponentTick.bCanEverTick = true;

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


		// They are initial data of each attributes. Theoretical limitation will be implemented later
		max_hit_points_ = stat_.hit_point_;
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

	for (FBuff& buff : buffs_)
	{
		if (buff.is_permanent_)
		{
			continue;
		}
		buff.time_remaining_ -= DeltaTime;
	}

	buffs_.RemoveAll([](const FBuff& buff)
		{
			return buff.is_permanent_ == false && buff.time_remaining_ <= 0.f;
		});
}

bool UCharacterStatComponent::GetDamage(float DamageAmount, AActor* Attacker)
{
	return GetDamage(DamageAmount, TWeakObjectPtr<AActor>(Attacker));
}

bool UCharacterStatComponent::GetDamage(float DamageAmount, TWeakObjectPtr<AActor> Attacker)
{
	float evasion_rand = FMath::RandRange(0.f, 1.f);
	bool is_damaged = evasion_rand >= GetEvasion();

	if (is_damaged && Attacker.IsValid())
	{
		AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		game_mode->RecordDamage(DamageAmount, Attacker);
	}

	// Display damage amount when damaged
	if (damage_UI_class_)
	{
		UDamageUI* damage_UI = CreateWidget<UDamageUI>(GetWorld(), damage_UI_class_);
		if (damage_UI)
		{
			damage_UI->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f));
			if (is_damaged)
			{
				damage_UI->SetDamageAmount(DamageAmount);
			}
			else
			{
				damage_UI->SetMissed();
			}
			damage_UI->AddToViewport();

			FVector2D screen_position;
			UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(GetWorld(), 0), GetOwner()->GetActorLocation(), screen_position);
			damage_UI->SetPositionInViewport(screen_position);

			// Add an animation to remove it after seconds.
			FTimerHandle timer_handle;
			GetWorld()->GetTimerManager().SetTimer(timer_handle, [damage_UI]()
				{
					damage_UI->RemoveFromParent();
				}, 0.75f, false);
		}
	}


	if (!is_damaged)
	{
		return false;
	}

	SetHitPoint(GetHitPoint() - DamageAmount);

	
	return true;
}

void UCharacterStatComponent::Heal(float HealAmount)
{
	// Display damage amount when damaged
	if (damage_UI_class_)
	{
		UDamageUI* damage_UI = CreateWidget<UDamageUI>(GetWorld(), damage_UI_class_);
		if (damage_UI)
		{
			damage_UI->SetColorAndOpacity(FLinearColor(0.f, 1.f, 0.f));
			damage_UI->SetDamageAmount(HealAmount);
			damage_UI->AddToViewport();

			FVector2D screen_position;
			UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(GetWorld(), 0), GetOwner()->GetActorLocation(), screen_position);
			damage_UI->SetPositionInViewport(screen_position);

			// Add an animation to remove it after seconds.
			FTimerHandle timer_handle;
			GetWorld()->GetTimerManager().SetTimer(timer_handle, [damage_UI]()
				{
					damage_UI->RemoveFromParent();
				}, 0.75f, false);
		}
	}

	SetHitPoint(GetHitPoint() + HealAmount);
}

float UCharacterStatComponent::GetAbilityPower() const noexcept
{
	return CalculateStat(ECharacterStatType::AbillityPower);
}

float UCharacterStatComponent::GetAttack() const noexcept
{
	return CalculateStat(ECharacterStatType::Attack);
}

float UCharacterStatComponent::GetAttackSpeed() const noexcept
{
	return CalculateStat(ECharacterStatType::AttackSpeed);
}

float UCharacterStatComponent::GetHitPoint() const noexcept
{
	return CalculateStat(ECharacterStatType::HitPoints);
}

float UCharacterStatComponent::GetMagazine() const noexcept
{
	return CalculateStat(ECharacterStatType::Magazine);
}

float UCharacterStatComponent::GetFireRange() const noexcept
{
	return CalculateStat(ECharacterStatType::FireRange);
}

float UCharacterStatComponent::GetMoveSpeed() const noexcept
{
	return CalculateStat(ECharacterStatType::MoveSpeed);
}

float UCharacterStatComponent::GetSightRange() const noexcept
{
	return CalculateStat(ECharacterStatType::SightRange);
}

float UCharacterStatComponent::GetEvasion() const noexcept
{
	return CalculateStat(ECharacterStatType::Evasion);
}

void UCharacterStatComponent::SetAbilityPower(float ability_power) noexcept
{
	stat_.ability_power_ = ability_power;
}

void UCharacterStatComponent::SetAttack(float attack) noexcept
{
	stat_.attack_ = attack;
}

void UCharacterStatComponent::SetAttackSpeed(float attack_speed) noexcept
{
	stat_.attack_speed_ = attack_speed;
}

void UCharacterStatComponent::SetHitPoint(float hit_point) noexcept
{
	stat_.hit_point_ = FMath::Min(hit_point, GetMaxHitPoint());

	OnHPChanged.Broadcast();
	if (stat_.hit_point_ < KINDA_SMALL_NUMBER)
	{
		stat_.hit_point_ = 0.f;
		Die.Broadcast();
	}
}

void UCharacterStatComponent::SetMagazine(float magazine) noexcept
{
	stat_.magazine_ = magazine;
}

void UCharacterStatComponent::SetFireRange(float fire_range) noexcept
{
	stat_.fire_range_ = fire_range;
}

void UCharacterStatComponent::SetMoveSpeed(float move_speed) noexcept
{
	stat_.move_speed_ = move_speed;
}

void UCharacterStatComponent::SetSightRange(float sight_range) noexcept
{
	stat_.sight_range_ = sight_range;
}

float UCharacterStatComponent::GetHPRatio() const noexcept
{	// Don't calculate buffs because it calculates RATIO. The number caused by buffs will be simplified.
	if (max_hit_points_ < KINDA_SMALL_NUMBER)
	{
		return 0.f;
	}
	else
	{
		return stat_.hit_point_ / max_hit_points_;
	}
}

float UCharacterStatComponent::GetMaxHitPoint() const noexcept
{
	float stat = max_hit_points_;
	float percentage_bonus = 0.f;
	float value_bonus = 0.f;

	for (const FBuff& buff : buffs_)
	{
		if (buff.stat_type_ == ECharacterStatType::HitPoints)
		{
			if (buff.is_percentage_)
			{
				percentage_bonus += buff.value_;
			}
			else
			{
				value_bonus += buff.value_;
			}
		}
	}

	return (stat + value_bonus) * (1.f + percentage_bonus);
}

FCharacterData UCharacterStatComponent::GetCharacterData() const noexcept
{
	return stat_;
}

void UCharacterStatComponent::SetCharacterData(const FCharacterData& character_data) noexcept
{
	stat_ = character_data;
}

EDPType UCharacterStatComponent::GetPeriodicDP() const noexcept
{
	return stat_.periodic_dp_;
}

void UCharacterStatComponent::SetPeriodicDP(const EDPType& dp_data) noexcept
{
	stat_.periodic_dp_ = dp_data;
}

EDPType UCharacterStatComponent::GetGeneralDP() const noexcept
{
	return stat_.general_dp_;
}

void UCharacterStatComponent::SetGeneralDP(const EDPType& dp_data) noexcept
{
	stat_.general_dp_ = dp_data;
}

float UCharacterStatComponent::CalculateStat(ECharacterStatType StatType) const
{
	float stat = GetBaseStat(StatType);

	float percentage_bonus = 1.f;
	float value_bonus = 0.f;

	for (const FBuff& buff : buffs_)
	{
		if (buff.stat_type_ == StatType)
		{
			if (buff.is_percentage_)
			{
				percentage_bonus *= buff.value_;
			}
			else
			{
				value_bonus += buff.value_;
			}
		}
	}

	return (stat + value_bonus) * percentage_bonus;
}

float UCharacterStatComponent::GetBaseStat(ECharacterStatType StatType) const
{
	switch (StatType)
	{
	case ECharacterStatType::AbillityPower:
		return stat_.ability_power_;
		break;
	case ECharacterStatType::Attack:
		return stat_.attack_;
		break;
	case ECharacterStatType::AttackSpeed:
		return stat_.attack_speed_;
		break;
	case ECharacterStatType::HitPoints:
		return stat_.hit_point_;
		break;
	case ECharacterStatType::Magazine:
		return stat_.magazine_;
		break;
	case ECharacterStatType::FireRange:
		return stat_.fire_range_;
		break;
	case ECharacterStatType::MoveSpeed:
		return stat_.move_speed_;
		break;
	case ECharacterStatType::SightRange:
		return stat_.sight_range_;
		break;
	case ECharacterStatType::Evasion:
		return stat_.evasion_;
	default:
		break;
	}
	return 0.f;
}

void UCharacterStatComponent::ApplyBuff(FBuff buff)
{	// @@ TODO: Implement here to distinguish stackable vs non-stackable buffs.
	buffs_.Add(buff);
}

bool UCharacterStatComponent::RemoveBuff(FName BuffName)
{
	int32 found_index = buffs_.IndexOfByPredicate([BuffName](const FBuff& buff) {
		return buff.buff_name_ == BuffName;
		});

	if (found_index != INDEX_NONE)
	{
		buffs_.RemoveAt(found_index);
		return true;
	}

	return false;
}

TArray<FBuff> UCharacterStatComponent::GetBuffs() const
{
	return buffs_;
}
