// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Fire.h"

#include "Gunner.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Display, TEXT("Task_Reload::Fire"));
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AGunner* casted_gunner = Cast<AGunner>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* attack_target = Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName));
	if(attack_target) casted_gunner->Fire(attack_target);
	EBTNodeResult::Type return_value = EBTNodeResult::Failed;
	GetWorld()->GetTimerManager().SetTimer(timer_handle_, FTimerDelegate::CreateWeakLambda(this, [&]()
			{
				return_value = EBTNodeResult::Succeeded;
				UE_LOG(LogTemp, Display, TEXT("Fire Interval Complete"));
			}), casted_gunner->GetFireInterval(), false);
	
	return return_value;
}
