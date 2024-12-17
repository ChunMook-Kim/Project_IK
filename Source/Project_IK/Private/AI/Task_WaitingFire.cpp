/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Source file for Waiting Fire Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "AI/Task_WaitingFire.h"

#include "Interfaces/GunnerInterface.h"
#include "AIController.h"

UTask_WaitingFire::UTask_WaitingFire()
{
	NodeName = "WaitingFire";
}

EBTNodeResult::Type UTask_WaitingFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(	IGunnerInterface* casted_gunner = Cast<IGunnerInterface>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		casted_gunner->WaitNextFire();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}