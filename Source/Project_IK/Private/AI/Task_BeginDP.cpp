/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Source file for BeginDP Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_BeginDP.h"

#include "AIController.h"
#include "Weapons/Drone.h"

UTask_BeginDP::UTask_BeginDP()
{
	NodeName = "BeginDP";
}

EBTNodeResult::Type UTask_BeginDP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(	ADrone* casted_drone = Cast<ADrone>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		casted_drone->ActivateDronePlugin();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
