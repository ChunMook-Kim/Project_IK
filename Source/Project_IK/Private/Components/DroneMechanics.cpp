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
		periodic_plugin_->StartPassiveSkill();
		if(auto ai_controller = Cast<ADroneAIC>(Cast<APawn>(GetOwner())->Controller))
		{
			ai_controller->SetDPState(EDPState::WaitingDP);
		}
	}
}

void UDroneMechanics::WaitForHoldTime()
{
	if(GetWorld()->GetTimerManager().IsTimerActive(hold_time_handle_) == false)
	{
		if(GetPeriodicPluginHoldTime() == 0.f)
		{
			FinishHoldTime();
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(hold_time_handle_, this, &UDroneMechanics::FinishHoldTime, GetPeriodicPluginHoldTime());
		}
	}
}

void UDroneMechanics::FinishHoldTime()
{
	GetWorld()->GetTimerManager().ClearTimer(hold_time_handle_);
	if(auto ai_controller = Cast<ADroneAIC>(Cast<APawn>(GetOwner())->Controller))
	{
		ai_controller->SetDPState(EDPState::BeginDP);
	}
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
		}
	}
}

void UDroneMechanics::RemoveGeneralPlugIn()
{
	if(general_plugin_ != nullptr)
	{
		general_plugin_->Destroy();
	}
	general_plugin_ = nullptr;
}