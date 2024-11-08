// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_MoveToActorWithAbort.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UTask_MoveToActorWithAbort : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_MoveToActorWithAbort();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector destination_actor_key_;
};
