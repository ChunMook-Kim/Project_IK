/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Source file for Finish Stun Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_FinishStun.h"

#include "AIController.h"
#include "Characters/Unit.h"

EBTNodeResult::Type UTask_FinishStun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if(	AUnit* casted_unit = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		UE_LOG(LogTemp, Display, TEXT("Finish Stun"));
		casted_unit->FinishStun();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
