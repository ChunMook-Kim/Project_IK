/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Source file for BeginPassive Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "AI/Task_BeginPassive.h"

#include "AIController.h"
#include "Interfaces/PassiveCaster.h"

UTask_BeginPassive::UTask_BeginPassive()
{
	NodeName = "BeginPassive";
}

EBTNodeResult::Type UTask_BeginPassive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(	IPassiveCaster* casted_gunner = Cast<IPassiveCaster>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		casted_gunner->ActivatePassive();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
