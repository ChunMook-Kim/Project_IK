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
#include "Abilities/PassiveMechanics.h"

UTask_BeginPassive::UTask_BeginPassive()
{
	NodeName = "BeginPassive";
}

EBTNodeResult::Type UTask_BeginPassive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto casted_pawn = OwnerComp.GetAIOwner()->GetPawn();
	auto component = casted_pawn->GetComponentByClass(UPassiveMechanics::StaticClass()); 
	if(auto casted_component = Cast<UPassiveMechanics>(component))
	{
		casted_component->ActivatePassiveSkill();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
