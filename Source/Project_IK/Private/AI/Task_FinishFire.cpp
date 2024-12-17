/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Source file for Finish Fire Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_FinishFire.h"

#include "AIController.h"
#include "Interfaces/GunnerInterface.h"

UTask_FinishFire::UTask_FinishFire()
{
	NodeName = "Finish Fire";
}

EBTNodeResult::Type UTask_FinishFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if(	IGunnerInterface* casted_gunner = Cast<IGunnerInterface>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		casted_gunner->FinishFire();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
