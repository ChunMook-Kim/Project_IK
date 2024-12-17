/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Source file for Waiting DP Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_WaitingDP.h"

#include "AIController.h"
#include "Weapons/Drone.h"

UTask_WaitingDP::UTask_WaitingDP()
{
	NodeName = "WaitingDP";
}

EBTNodeResult::Type UTask_WaitingDP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(	ADrone* casted_drone = Cast<ADrone>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		casted_drone->WaitForHoldTime();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
