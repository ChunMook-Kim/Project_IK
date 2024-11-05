// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Decorator_IsMagezineEmpty.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UDecorator_IsMagezineEmpty : public UBTDecorator
{
	GENERATED_BODY()
public:
	UDecorator_IsMagezineEmpty();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
