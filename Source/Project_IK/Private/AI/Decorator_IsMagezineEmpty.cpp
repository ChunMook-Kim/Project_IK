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
#include "Interfaces/GunnerInterface.h"

UDecorator_IsMagezineEmpty::UDecorator_IsMagezineEmpty()
{
	NodeName = "IsMagazineEmpty";
}

bool UDecorator_IsMagezineEmpty::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	IGunnerInterface* casted_gunner = Cast<IGunnerInterface>(OwnerComp.GetAIOwner()->GetPawn());
	if(casted_gunner)
	{
		return casted_gunner->IsMagazineEmpty();
	}
	UE_LOG(LogTemp, Error, TEXT("%s node can't find gunner!"), *NodeName);
	return false;
}