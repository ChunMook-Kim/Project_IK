/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Source file for weapon magazine empty check decorator.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Decorator_IsMagezineEmpty.h"

#include "AIController.h"
#include "Characters/Gunner.h"

UDecorator_IsMagezineEmpty::UDecorator_IsMagezineEmpty()
{
	NodeName = "IsMagezineEmpty";
}

bool UDecorator_IsMagezineEmpty::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AGunner* casted_gunner = Cast<AGunner>(OwnerComp.GetAIOwner()->GetPawn());
	return casted_gunner->IsMagazineEmpty();
}