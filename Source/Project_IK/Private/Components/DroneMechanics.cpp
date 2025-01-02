/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Source file for Drone Mechanics component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Components/DroneMechanics.h"
#include "Abilities/PassiveSkill.h"
#include "Abilities/DPI_FireRange.h"
#include "Abilities/DPI_FireRateBurst.h"
#include "AI/DroneAIC.h"

// Sets default values for this component's properties
UDroneMechanics::UDroneMechanics()
{
	PrimaryComponentTick.bCanEverTick = true;
	on_jammed_ = false;
}

// Called when the game starts
void UDroneMechanics::BeginPlay()
{
	Super::BeginPlay();
}

void UDroneMechanics::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(hold_time_handle_);
	Super::EndPlay(EndPlayReason);
}

void UDroneMechanics::Initialize(AActor* hero)
{
	hero_ref_ = hero;
}

void UDroneMechanics::GetJammed(float duration)
{
	//만약 밴된 도중에 다시 밴 된다면, 밴 시간만 조정한다.
	if(on_jammed_)
	{
		GetWorld()->GetTimerManager().SetTimer(jam_time_handle_, this, &UDroneMechanics::FinishJam, duration, false);
		return;
	}

	if(general_plugin_)
	{
		if(general_plugin_->IsOnPassiveSkill() || general_plugin_->IsPassiveAvailable())
		{
			general_plugin_->FinishPassiveSkillAndStartCoolDown();
		}
		general_plugin_->StartHoldCoolDown();
	}
	if(periodic_plugin_)
	{
		if(periodic_plugin_->IsOnPassiveSkill() || periodic_plugin_->IsPassiveAvailable())
		{
			periodic_plugin_->FinishPassiveSkillAndStartCoolDown();
		}
		periodic_plugin_->StartHoldCoolDown();
	}
	//duration동안 쿨타임이 돌지 못하게 한다.
	GetWorld()->GetTimerManager().SetTimer(jam_time_handle_, this, &UDroneMechanics::FinishJam, duration, false);
	on_jammed_ = true;
}

void UDroneMechanics::FinishJam()
{
	if(periodic_plugin_)
	{
		periodic_plugin_->FinishHoldCoolDown();
	}
	if(general_plugin_)
	{
		general_plugin_->FinishHoldCoolDown();
	}
	on_jammed_ = false;
}

float UDroneMechanics::GetPeriodicPluginHoldTime() const
{
	return periodic_plugin_->GetHoldTime();
}

void UDroneMechanics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UDroneMechanics::IsPeriodicPluginAvailable() const
{
	if(periodic_plugin_ != nullptr)
	{
		return periodic_plugin_->IsPassiveAvailable();
	}
	return false;
}

void UDroneMechanics::ActivatePeriodicDronePlugin()
{
	if(periodic_plugin_ != nullptr)
	{
		if(periodic_plugin_->IsPassiveAvailable())
		{
			periodic_plugin_->StartPassiveSkill();
		}
	}
}

void UDroneMechanics::FinishHoldTime()
{
	GetWorld()->GetTimerManager().ClearTimer(hold_time_handle_);
}

void UDroneMechanics::AddPeriodicPlugIn(UClass* plugin_type)
{
	if(plugin_type)
	{
		auto spawned_dp = Cast<ADronePlugIn>(GetWorld()->SpawnActor(plugin_type));
		if(spawned_dp->IsPeriodic() == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Assign General DP to Periodic!!"));
		}
		else
		{
			if(periodic_plugin_) RemovePeriodicPlugIn();
			periodic_plugin_ = spawned_dp;
			periodic_plugin_->Initialize(hero_ref_);
			periodic_plugin_->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}

void UDroneMechanics::AddGeneralPlugIn(UClass* plugin_type)
{
	if(plugin_type)
	{
		auto spawned_dp = Cast<ADronePlugIn>(GetWorld()->SpawnActor(plugin_type));
		if(spawned_dp->IsPeriodic() == true)
		{
			UE_LOG(LogTemp, Error, TEXT("Assign Periodic DP to General!!"));
		}
		else
		{
			if(general_plugin_) RemoveGeneralPlugIn();
			general_plugin_ = spawned_dp;
			general_plugin_->Initialize(hero_ref_);
			general_plugin_->StartPassiveSkill();
			general_plugin_->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}


void UDroneMechanics::RemovePeriodicPlugIn()
{
	if(periodic_plugin_ != nullptr)
	{
		periodic_plugin_->Destroy();
	}
	periodic_plugin_ = nullptr;
}

void UDroneMechanics::RemoveGeneralPlugIn()
{
	if(general_plugin_ != nullptr)
	{
		general_plugin_->Destroy();
	}
	general_plugin_ = nullptr;
}