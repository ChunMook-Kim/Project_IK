/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Source file for Begin Reload Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "AI/Task_BeginReload.h"

#include "AIController.h"
#include "Interfaces/GunnerInterface.h"

UTask_BeginReload::UTask_BeginReload()
{
	NodeName = "BeginReload";
}

EBTNodeResult::Type UTask_BeginReload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(	IGunnerInterface* casted_gunner = Cast<IGunnerInterface>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		casted_gunner->Reload();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
