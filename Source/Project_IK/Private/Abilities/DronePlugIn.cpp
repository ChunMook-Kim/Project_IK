/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Source file for the Drone Plugin base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/DronePlugIn.h"

ADronePlugIn::ADronePlugIn()
{
}

void ADronePlugIn::Initialize(AActor* hero)
{
	Super::Initialize(hero);
}

bool ADronePlugIn::IsPeriodic() const
{
	return is_periodic_;
}

void ADronePlugIn::SetPeriodic(bool bIs_Periodic)
{
	is_periodic_ = bIs_Periodic;
}
