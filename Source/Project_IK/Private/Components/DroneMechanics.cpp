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

void UDroneMechanics::Initialize(AActor* hero)
{
	hero_ref_ = hero;
	AddPeriodicPlugIn(ADPI_FireRateBurst::StaticClass());
	AddGeneralPlugIn(ADPI_FireRange::StaticClass());
}

void UDroneMechanics::ActivatePeriodicDronePlugin()
{
	if(periodic_plugin_ != nullptr)
	{
		periodic_plugin_->StartPassiveSkill();
	}
}

//만약 패시브를 사용 중 사망, 혹은 레벨 클리어 시 강제로 DP를 끝낼 때 사용된다.
void UDroneMechanics::ForceDeactivatePeriodicPlugin()
{
	if(periodic_plugin_ != nullptr)
	{
		if(periodic_plugin_->IsActivated() == true)
		{
			periodic_plugin_->FinishPassiveSkill();
			periodic_plugin_->SetActivated(false);
		}
	}
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
	else
	{
		return false;
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
		general_plugin_->FinishPassiveSkill();
		general_plugin_->Destroy();
	}
	general_plugin_ = nullptr;
}