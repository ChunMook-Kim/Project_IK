// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Decorator_IsPlugInAvailable.generated.h"
UCLASS()
class PROJECT_IK_API UDecorator_IsPlugInAvailable : public UBTDecorator
{
	GENERATED_BODY()

public:
	UDecorator_IsPlugInAvailable();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
