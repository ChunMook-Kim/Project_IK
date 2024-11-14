/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Source file for activate drone plugin by AI Task node. 

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_ActivateDronePlugIn.h"
#include "Weapons/Drone.h"
#include "AIController.h"

UTask_ActivateDronePlugIn::UTask_ActivateDronePlugIn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Activate Drone Plug In";
	bTickIntervals = true;
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UTask_ActivateDronePlugIn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ADrone* casted_drone = Cast<ADrone>(OwnerComp.GetAIOwner()->GetPawn());
	casted_drone->ActivateDronePlugin();
	
	SetNextTickTime(NodeMemory, casted_drone->GetDronePluginHoldTime());
	return EBTNodeResult::InProgress;
}

void UTask_ActivateDronePlugIn::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Using the SetNextTickTime in ExecuteTask we are certain we are only getting ticked when the wait is finished
	ensure(GetSpecialNodeMemory<FBTTaskMemory>(NodeMemory)->NextTickRemainingTime <= 0.f);

	// continue execution from this node
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	
}
