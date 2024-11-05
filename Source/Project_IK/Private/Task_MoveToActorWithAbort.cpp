// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_MoveToActorWithAbort.h"

UTask_MoveToActorWithAbort::UTask_MoveToActorWithAbort()
{
	NodeName = "MoveToActorAndStopByAbort";
}

EBTNodeResult::Type UTask_MoveToActorWithAbort::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UTask_MoveToActorWithAbort::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	return EBTNodeResult::Succeeded;
}
