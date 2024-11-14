/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Source file for the AI Decorator for check drone plugin availability.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Decorator_IsPlugInAvailable.h"

#include "Weapons/Drone.h"
#include "AIController.h"

UDecorator_IsPlugInAvailable::UDecorator_IsPlugInAvailable()
{
	NodeName = TEXT("UDecorator_IsPlugInAvailable");
}

bool UDecorator_IsPlugInAvailable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	ADrone* casted_drone = Cast<ADrone>(OwnerComp.GetAIOwner()->GetPawn());
	return casted_drone->IsPluginAvailable();
}
