/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Source file for activate passive skill task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_ActivatePassive.h"

#include "Characters/PassiveSkillGunner.h"
#include "AIController.h"

UTask_ActivatePassive::UTask_ActivatePassive(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Activate Passive";
	bTickIntervals = true;
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UTask_ActivatePassive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APassiveSkillGunner* casted_p_gunner = Cast<APassiveSkillGunner>(OwnerComp.GetAIOwner()->GetPawn());
	casted_p_gunner->ActivatePassive();
	SetNextTickTime(NodeMemory, casted_p_gunner->GetPassiveHoldTime());

	return EBTNodeResult::InProgress;
}

void UTask_ActivatePassive::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Using the SetNextTickTime in ExecuteTask we are certain we are only getting ticked when the wait is finished
	ensure(GetSpecialNodeMemory<FBTTaskMemory>(NodeMemory)->NextTickRemainingTime <= 0.f);

	// continue execution from this node
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}