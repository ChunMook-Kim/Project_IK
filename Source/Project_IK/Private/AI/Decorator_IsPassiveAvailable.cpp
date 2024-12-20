/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Source file for weapon magazine empty check decorator.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Decorator_IsPassiveAvailable.h"

#include "Interfaces/PassiveCaster.h"
#include "AIController.h"

UDecorator_IsPassiveAvailable::UDecorator_IsPassiveAvailable() 
{
	NodeName = TEXT("IsPassiveAvailable");
}

bool UDecorator_IsPassiveAvailable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if(	IPassiveCaster* casted_passive_caster = Cast<IPassiveCaster>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		return casted_passive_caster->IsPassiveAvailable();
	}
	UE_LOG(LogTemp, Error, TEXT("%s node can't find passive caster!"), *NodeName);
	return false;
}
