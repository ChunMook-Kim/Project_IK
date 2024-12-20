// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_Aimming.generated.h"

/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.05.2024
Summary : Header file for Aimming Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
UCLASS()
class PROJECT_IK_API UTask_Aimming : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_Aimming();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector attack_target_key_;
};
