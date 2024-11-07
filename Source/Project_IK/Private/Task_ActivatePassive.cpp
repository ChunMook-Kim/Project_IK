// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_ActivatePassive.h"

#include "PassiveSkillGunner.h"
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
