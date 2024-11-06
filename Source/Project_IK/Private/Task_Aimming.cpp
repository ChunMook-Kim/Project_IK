/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.05.2024
Summary : Source file for Aimming Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Task_Aimming.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UTask_Aimming::UTask_Aimming()
{
	NodeName = "Aimming";
}

EBTNodeResult::Type UTask_Aimming::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AAIController* owner_controller_ = OwnerComp.GetAIOwner();
	owner_controller_->SetFocus(Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName)));
	return EBTNodeResult::Succeeded;
}
