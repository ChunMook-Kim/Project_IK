// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorator_IsMagezineEmpty.h"

#include "AIController.h"
#include "Gunner.h"

UDecorator_IsMagezineEmpty::UDecorator_IsMagezineEmpty()
{
	NodeName = "IsMagezineEmpty";
}

bool UDecorator_IsMagezineEmpty::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AGunner* casted_gunner = Cast<AGunner>(OwnerComp.GetAIOwner()->GetPawn());
	return casted_gunner->IsMegazineEmpty();
}