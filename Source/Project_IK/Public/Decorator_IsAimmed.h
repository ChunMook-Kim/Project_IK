// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Decorator_IsAimmed.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UDecorator_IsAimmed : public UBTDecorator
{
	GENERATED_BODY()
public:
	UDecorator_IsAimmed();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector attack_target_key_;
};
