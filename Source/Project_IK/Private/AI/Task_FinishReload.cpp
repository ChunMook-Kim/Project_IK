/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Source file for Finish Reload Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_FinishReload.h"

#include "AIController.h"
#include "Interfaces/GunnerInterface.h"

UTask_FinishReload::UTask_FinishReload()
{
	NodeName = "Finish Reload";
}

EBTNodeResult::Type UTask_FinishReload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(	IGunnerInterface* casted_gunner = Cast<IGunnerInterface>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		casted_gunner->FinishReload();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;}
