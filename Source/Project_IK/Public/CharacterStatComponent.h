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
#include "CharacterStatComponent.generated.h"

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

	// Getters&Setters of member variables
	float GetAbilityPower() noexcept;
	float GetAttack() noexcept;
	float GetAttackSpeed() noexcept;
	float GetHitPoint() noexcept;
	float GetMagazine() noexcept;
	float GetFireRange() noexcept;
	float GetMoveSpeed() noexcept;
	float GetSightRange() noexcept;

	void SetAbilityPower(float ability_power) noexcept;
	void SetAttack(float attack) noexcept;
	void SetAttackSpeed(float attack_speed) noexcept;
	void SetHitPoint(float hit_point) noexcept;
	void SetMagazine(float magazine) noexcept;
	void SetFireRange(float fire_range) noexcept;
	void SetMoveSpeed(float move_speed) noexcept;
	void SetSightRange(float sight_range) noexcept;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Stats)
	int32 character_id_;

private:
	// Scaling powers
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float ability_power_;
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float attack_;
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float attack_speed_;
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float hit_point_;
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float magazine_;

	// Fixed powers
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float fire_range_;
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float move_speed_;
	UPROPERTY(VisibleInstanceOnly, Category = Stats, Meta = (AllowPrivateAccess = true))
	float sight_range_;


	float max_ability_power_;
	float max_attack_;
	float max_attack_speed_;
	float max_hit_point_;
	float max_magazine_;

	float max_fire_range_;
	float max_move_speed_;
	float max_sight_range_;
};
