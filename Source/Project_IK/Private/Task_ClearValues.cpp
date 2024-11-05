/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.05.2024
Summary : Source file for  Clear Values Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Task_ClearValues.h"

#include "BehaviorTree/BlackboardComponent.h"

UTask_ClearValues::UTask_ClearValues()
{
	NodeName = "Clear attack target and cover ownership.";
}

EBTNodeResult::Type UTask_ClearValues::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	blackboard->ClearValue(owned_cover_key_.GetSelectedKeyID());
	blackboard->ClearValue(attack_target_key_.GetSelectedKeyID());
	return EBTNodeResult::Succeeded;
}
