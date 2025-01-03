/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.23.2024
Summary : Source file to manage CC(crowd control) effects.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Components/CrowdControlComponent.h"

#include "GameFramework/PlayerController.h"
#include "WorldSettings/IKHUD.h"

#include "Characters/Unit.h"
#include "AI/MeleeAIController.h"

// Sets default values for this component's properties
UCrowdControlComponent::UCrowdControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UCrowdControlComponent::ApplyCrowdControl(ECCType cc_type, float duration)
{
	if (HasCrowdControl(cc_type))
	{
		// Update only timer if existed.
		FTimerHandle timer_handle = CC_timers_[cc_type];
		UWorld* world = GetWorld();
		if (world)
		{
			world->GetTimerManager().SetTimer(timer_handle, [this, cc_type]() 
				{
					RemoveCrowdControl(cc_type);
				}, duration, false);
		}
	}
	else
	{
		// Apply cc
		FTimerHandle timer_handle;
		UWorld* world = GetWorld();
		if (world)
		{
			world->GetTimerManager().SetTimer(timer_handle, [this, cc_type]() 
				{
					RemoveCrowdControl(cc_type);
				}, duration, false);

			CC_timers_.Add(cc_type, timer_handle);
		}
		OnCrowdControlChanged.Broadcast();
	}

	BeginCC(cc_type, duration);
}

void UCrowdControlComponent::RemoveCrowdControl(ECCType cc_type)
{
	if (!HasCrowdControl(cc_type))
	{
		return;
	}

	// clear Timer 
	UWorld* world = GetWorld();
	if (world)
	{
		world->GetTimerManager().ClearTimer(CC_timers_[cc_type]);
		CC_timers_.Remove(cc_type);
		OnCrowdControlChanged.Broadcast();
	}
	
	EndCC(cc_type);
}

void UCrowdControlComponent::RemoveAllCrowdControl()
{
	UWorld* world = GetWorld();
	if (!world)
	{
		return;
	}

	for (TPair<ECCType, FTimerHandle> pair : CC_timers_)
	{
		world->GetTimerManager().ClearTimer(pair.Value);
		EndCC(pair.Key);
	}

	CC_timers_.Empty();
	OnCrowdControlChanged.Broadcast();
}


bool UCrowdControlComponent::HasCrowdControl(ECCType cc_type) const
{
	return CC_timers_.Contains(cc_type);
}

TArray<ECCType> UCrowdControlComponent::GetAppliedCCArray() const
{
	TArray<ECCType> cc;
	for (TPair<ECCType, FTimerHandle> pair : CC_timers_)
	{
		cc.Add(pair.Key);
	}
	return cc;
}

void UCrowdControlComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UWorld* world = GetWorld();
	if (!world)
	{
		return;
	}
	FTimerManager& timer_manager = world->GetTimerManager();

	for (TPair<ECCType, FTimerHandle> pair : CC_timers_)
	{
		// Clear timer
		timer_manager.ClearTimer(pair.Value);
	}
}

void UCrowdControlComponent::BeginCC(ECCType cc_type, float duration)
{
	switch (cc_type)
	{
	case ECCType::DroneJamming:
		DroneJamming();
		break;
	case ECCType::Silence:
		Silence();
		break;
	case ECCType::MuteItems:
		MuteItems();
		break;
	case ECCType::Stun:
		Stun(duration);
		break;
	default:
		break;
	}
}

void UCrowdControlComponent::EndCC(ECCType cc_type)
{
	// Do something when cc has resolved
	switch (cc_type)
	{
	case ECCType::DroneJamming:
		DroneJamming(false);
		break;
	case ECCType::Silence:
		Silence(false);
		break;
	case ECCType::MuteItems:
		MuteItems(false);
		break;
	case ECCType::Stun:
		Stun(false);
		break;
	default:
		break;
	}
}

void UCrowdControlComponent::DroneJamming(bool is_applying)
{
	if (is_applying)
	{
		// @@ TODO: Applying jamming drone
	}
	else
	{
		// @@ TODO: Removing jamming drone
	}
}

void UCrowdControlComponent::Silence(bool is_applying)
{
	UWorld* world = GetWorld();
	if (world)
	{
		APlayerController* player_controller = world->GetFirstPlayerController();
		if (player_controller)
		{
			AIKHUD* HUD = Cast<AIKHUD>(player_controller->GetHUD());
			if (is_applying)
			{
				HUD->SilenceSkill(GetOwner());
			}
			else
			{
				HUD->UnsilenceSkill(GetOwner());
			}
		}
	}
}

void UCrowdControlComponent::MuteItems(bool is_applying)
{
	UWorld* world = GetWorld();
	if (world)
	{
		APlayerController* player_controller = world->GetFirstPlayerController();
		if (player_controller)
		{
			AIKHUD* HUD = Cast<AIKHUD>(player_controller->GetHUD());
			if (is_applying)
			{
				HUD->MuteItems();
			}
			else
			{
				HUD->UnmuteItems();
			}
		}
	}
}

void UCrowdControlComponent::Stun(float duration, bool is_applying)
{
	if (is_applying)
	{
		AUnit* unit = Cast<AUnit>(GetOwner());
		unit->GetStunned(duration);
	}
	else
	{
		// @@ TODO: Removing Stun
	}
}
