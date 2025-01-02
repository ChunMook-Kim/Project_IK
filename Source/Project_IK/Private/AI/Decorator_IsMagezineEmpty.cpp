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
#include "Components/WeaponMechanics.h"

UDecorator_IsMagezineEmpty::UDecorator_IsMagezineEmpty()
{
	NodeName = "IsMagazineEmpty";
}

bool UDecorator_IsMagezineEmpty::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto casted_pawn = OwnerComp.GetAIOwner()->GetPawn();
	auto component = casted_pawn->GetComponentByClass(UWeaponMechanics::StaticClass()); 
	if(auto casted_component = Cast<UWeaponMechanics>(component))
	{
		return casted_component->IsMagazineEmpty();
	}
	UE_LOG(LogTemp, Error, TEXT("%s node can't find gunner!"), *NodeName);
	return false;
}