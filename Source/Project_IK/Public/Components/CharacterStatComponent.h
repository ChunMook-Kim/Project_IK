/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.14.2024
Summary : Header file for Character Stat class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Managers/CharacterDataManager.h"
#include "CharacterStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDieDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UENUM(BlueprintType)
enum class ECharacterID : uint8
{
	Gunner UMETA(DisplayName = "Gunner"),
	Cover UMETA(DisplayName = "Cover"),
};

UENUM(BlueprintType)
enum class ECharacterStatType : uint8
{
	AbillityPower UMETA(DisplayName = "AbilityPower"),
	Attack UMETA(DisplayName = "Attack"),
	AttackSpeed UMETA(DisplayName = "AttackSpeed"),
	HitPoints UMETA(DisplayName = "HitPoints"),
	Magazine UMETA(DisplayName = "Magazine"),
	FireRange UMETA(DisplayName = "FireRange"),
	MoveSpeed UMETA(DisplayName = "MoveSpeed"),
	SightRange UMETA(DisplayName = "SightRange"),
};

USTRUCT(BlueprintType)
struct FBuff
{
public:
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Buff")
	ECharacterStatType  stat_type_;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Buff")
	float value_;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Buff")
	bool is_percentage_;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Buff")
	float duration_;

	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadWrite, Category = "Buff")
	float time_remaining_;



	FBuff()
		: stat_type_(ECharacterStatType::Attack), value_(0.f), is_percentage_(false), duration_(0.f), time_remaining_(0.f)
	{}

	FBuff(ECharacterStatType StatType, float Value, bool IsPercentage, float Duration)
		: stat_type_(StatType), value_(Value), is_percentage_(IsPercentage), duration_(Duration), time_remaining_(Duration)
	{}
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_IK_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UCharacterStatComponent();

	virtual void InitializeComponent() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunctionoverride);

	UFUNCTION(BlueprintCallable)
	void GetDamage(float DamageAmount);

	// Getters&Setters of member variables
	UFUNCTION(BlueprintPure)
	float GetAbilityPower() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetAttack() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetAttackSpeed() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetHitPoint() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetMagazine() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetFireRange() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetMoveSpeed() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetSightRange() const noexcept;

	UFUNCTION(BlueprintCallable)
	void SetAbilityPower(float ability_power) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetAttack(float attack) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetAttackSpeed(float attack_speed) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetHitPoint(float hit_point) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetMagazine(float magazine) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetFireRange(float fire_range) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetMoveSpeed(float move_speed) noexcept;
	UFUNCTION(BlueprintCallable)
	void SetSightRange(float sight_range) noexcept;

	UFUNCTION(BlueprintPure)
	float GetHPRatio() const noexcept;

	UFUNCTION(BlueprintPure)
	float GetMaxHitPoint() const noexcept;

	UFUNCTION(BlueprintPure)
	FCharacterData GetCharacterData() const noexcept;

	UFUNCTION(BlueprintCallable)
	void SetCharacterData(const FCharacterData& character_data) noexcept;

	UFUNCTION(BlueprintCallable)
	float CalculateStat(ECharacterStatType StatType) const;

	UFUNCTION(BlueprintCallable)
	float GetBaseStat(ECharacterStatType StatType) const;

	UFUNCTION(BlueprintCallable)
	void ApplyBuff(FBuff buff);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FDieDelegate Die;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHPChangedDelegate OnHPChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Stats")
	ECharacterID character_id_;

private:
	// Scaling powers
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	FCharacterData stat_;

	float max_hit_points_;

	TArray<FBuff> buffs_;
};
