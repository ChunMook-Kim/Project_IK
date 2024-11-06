// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_Fire.generated.h"

struct FBTWaitTaskMemory
{
};

UCLASS(MinimalAPI)
class UTask_Fire : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponMechanics", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector attack_target_key_;
};
