// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Aimming.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UTask_Aimming::UTask_Aimming()
{
	NodeName = "Aimming";
}

EBTNodeResult::Type UTask_Aimming::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AAIController* owner_controller_ = OwnerComp.GetAIOwner();
	owner_controller_->SetFocus(Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName)));
	return EBTNodeResult::Succeeded;
}
