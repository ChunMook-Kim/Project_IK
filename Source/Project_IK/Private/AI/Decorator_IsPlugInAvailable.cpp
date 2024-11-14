// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator_IsPlugInAvailable.h"

#include "Weapons/Drone.h"
#include "AIController.h"

UDecorator_IsPlugInAvailable::UDecorator_IsPlugInAvailable()
{
	NodeName = TEXT("UDecorator_IsPlugInAvailable");
}

bool UDecorator_IsPlugInAvailable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	ADrone* casted_drone = Cast<ADrone>(OwnerComp.GetAIOwner()->GetPawn());
	return casted_drone->IsPluginAvailable();
}
