/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Header file for check passive skill availability decorator.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Decorator_IsPassiveAvailable.generated.h"
UCLASS()
class PROJECT_IK_API UDecorator_IsPassiveAvailable : public UBTDecorator
{
	GENERATED_BODY()

public:
	UDecorator_IsPassiveAvailable();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
