/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Source file for Begin Stun Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_BeginStun.h"

#include "AIController.h"
#include "Characters/Unit.h"

EBTNodeResult::Type UTask_BeginStun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(	AUnit* casted_unit = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		casted_unit->GetStunned();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
