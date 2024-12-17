/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Header file for Waiting Passive Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_WaitingPassive.h"

#include "AIController.h"
#include "Interfaces/PassiveCaster.h"

UTask_WaitingPassive::UTask_WaitingPassive()
{
	NodeName = "WaitingPassive";
}

EBTNodeResult::Type UTask_WaitingPassive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(	IPassiveCaster* casted_caster = Cast<IPassiveCaster>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		casted_caster->WaitForHoldTime();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
