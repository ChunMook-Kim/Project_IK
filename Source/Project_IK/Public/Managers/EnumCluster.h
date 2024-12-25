/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.04.2024
Summary : Header file for the EnumCluster.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnumCluster.generated.h"

UENUM(BlueprintType)
enum class EDPType : uint8
{
	Empty UMETA(DisplayName = "Empty"),
	FireRateBurst UMETA(DisplayName = "Fire Rate"),
	FireRange UMETA(DisplayName = "Fire Range"),
	HealingWaves UMETA(DisplayName = "Healing Waves"),
	LaserBeam UMETA(DisplayName = "LaserBeam"),
	INVALID UMETA(DisplayName = "Invalid")
};

UENUM(BlueprintType)
enum class EUnitState  : uint8
{
	Forwarding UMETA(DisplayName = "Forwarding"),
	HeadingToEnemy UMETA(DisplayName = "Heading To Enemy"),
	HeadingToCover UMETA(DisplayName = "Heading To Cover"),
	Attacking UMETA(DisplayName = "Attacking"),
	Stunned UMETA(DisplayName = "Stunned"),
};

UENUM(BlueprintType)
enum class EFireState  : uint8
{
	BeginFire UMETA(DisplayName = "BeginFire"),
	WaitingFire UMETA(DisplayName = "WaitingFire"),
	FinishFire UMETA(DisplayName = "FinishFire")
};

UENUM(BlueprintType)
enum class EReloadState  : uint8
{
	BeginReload UMETA(DisplayName = "BeginReload"),
	WaitingReload UMETA(DisplayName = "WaitingReload"),
	FinishReload UMETA(DisplayName = "FinishReload")
};

UENUM(BlueprintType)
enum class EPassiveState  : uint8
{
	BeginPassive UMETA(DisplayName = "BeginPassive"),
	WaitingHoldTime UMETA(DisplayName = "WaitingHoldTime"),
	FinishHoldTime UMETA(DisplayName = "FinishHoldTime")
};

UENUM(BlueprintType)
enum class EStunState  : uint8
{
	BeginStun UMETA(DisplayName = "BeginStun"),
	WaitingStun UMETA(DisplayName = "WaitingStun"),
	FinishStun UMETA(DisplayName = "FinishStun")
};

UENUM(BlueprintType)
enum class EDPState  : uint8
{
	BeginDP UMETA(DisplayName = "BeginDP"),
	WaitingDP UMETA(DisplayName = "WaitingDP"),
	FinishDP UMETA(DisplayName = "FinishDP")
};

UENUM(BlueprintType)
enum class EDroneState  : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	UsingPeriodicDP UMETA(DisplayName = "UsingPeriodicDP"),
	UsingGeneralDP UMETA(DisplayName = "UsingGeneralDP")
};


UENUM(BlueprintType)
enum class ECCType : uint8
{
	DroneJamming UMETA(DisplayName = "DroneJamming"),
	Silence UMETA(DisplayName = "Silence"),
	MuteItems UMETA(DisplayName = "ItemDisabled"),
	Stun UMETA(DisplayName = "Stun"),
};

UENUM(BlueprintType)
enum class NodeType : uint8
{
	None UMETA(DisplayName = "None"),
	Enemy UMETA(DisplayName = "Enemy"),
};

UENUM(BlueprintType)
enum class ELevelEndState : uint8
{
	ShowingCombatResultUI UMETA(DisplayName = "ShowingCombatResultUI"),
	ShowingItemPickerUI UMETA(DisplayName = "ShowingItemPickerUI"),
	ShowingMapUI UMETA(DisplayName = "ShowingMapUI"),
};

UENUM(BlueprintType)
enum class EItemLogicType : uint8
{
	None UMETA(DisplayName = "None"),
	RestoreHP UMETA(DisplayName = "RestoreHP"),
	LaunchMissile UMETA(DisplayName = "LaunchMissile"),
	AttackSpeedStimuli UMETA(DisplayName = "AttackSpeedStimuli"),
	SmokeGrenade UMETA(DisplayName = "SmokeGrenade"),
	Flashbang UMETA(DisplayName = "Flashbang"),
};

UENUM(BlueprintType)
enum class ETargetingMode : uint8
{
	None UMETA(DisplayName = "None"),
	Actor UMETA(DisplayName = "Actor"),
	Location UMETA(DisplayName = "Location"),
	Direction UMETA(DisplayName = "Direction"),
};

UENUM(BlueprintType)
enum class ETargetType : uint8
{
	None UMETA(DisplayName = "None"),
	Allies UMETA(DisplayName = "Allies"),
	Opponents UMETA(DisplayName = "Opponents"),
	All UMETA(DisplayName = "All"),
};