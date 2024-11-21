/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Header file for Weapon Reload. Algorithm is came from BTTask_Wait.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_Reload.h"

#include "AIController.h"
#include "Interfaces/GunnerInterface.h"

UTask_Reload::UTask_Reload(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Reload";
	bTickIntervals = true;
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UTask_Reload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	IGunnerInterface* casted_gunner = Cast<IGunnerInterface>(OwnerComp.GetAIOwner()->GetPawn());
	casted_gunner->Reload();

	SetNextTickTime(NodeMemory, casted_gunner->GetReloadDuration());
	return EBTNodeResult::InProgress;
}

void UTask_Reload::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Using the SetNextTickTime in ExecuteTask we are certain we are only getting ticked when the wait is finished
	ensure(GetSpecialNodeMemory<FBTTaskMemory>(NodeMemory)->NextTickRemainingTime <= 0.f);
	
	// continue execution from this node
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
