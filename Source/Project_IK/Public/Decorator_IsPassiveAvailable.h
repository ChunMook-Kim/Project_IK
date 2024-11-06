// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Decorator_IsPassiveAvailable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UDecorator_IsPassiveAvailable : public UBTDecorator
{
	GENERATED_BODY()

public:
	UDecorator_IsPassiveAvailable();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
