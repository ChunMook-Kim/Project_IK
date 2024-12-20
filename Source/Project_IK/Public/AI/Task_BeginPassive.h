/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Header file for BeginPassive Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_BeginPassive.generated.h"


UCLASS()
class PROJECT_IK_API UTask_BeginPassive : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_BeginPassive();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
