// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorator_IsPassiveAvailable.h"

#include "PassiveSkillGunner.h"
#include "AIController.h"

UDecorator_IsPassiveAvailable::UDecorator_IsPassiveAvailable() 
{
	NodeName = TEXT("IsPassiveAvailable");
}

bool UDecorator_IsPassiveAvailable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APassiveSkillGunner* casted_p_gunner = Cast<APassiveSkillGunner>(OwnerComp.GetAIOwner()->GetPawn());
	return casted_p_gunner->IsPassiveAvailable();
}
