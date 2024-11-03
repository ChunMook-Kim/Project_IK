// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "FindNearestEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UFindNearestEnemy : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UFindNearestEnemy();
	//TODO: PROPERTY달아야 함.
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	//TODO: PROPERTY달아야 함.
	FBlackboardKeySelector target_class_key_;
	FBlackboardKeySelector target_enemy_key_;
};
