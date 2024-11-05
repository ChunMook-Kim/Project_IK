// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Reload.h"

#include "TimerManager.h"
#include "AIController.h"
#include "Gunner.h"


EBTNodeResult::Type UTask_Reload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Display, TEXT("Task_Reload::ExecuteTask"));
	AGunner* casted_gunner = Cast<AGunner>(OwnerComp.GetAIOwner()->GetPawn());
	EBTNodeResult::Type return_value = EBTNodeResult::Failed;
	GetWorld()->GetTimerManager().SetTimer(timer_handle_, FTimerDelegate::CreateWeakLambda(this, [&]()
			{
				casted_gunner->Reload();
				return_value = EBTNodeResult::Succeeded;
				UE_LOG(LogTemp, Display, TEXT("Reload Complete"));
			}), casted_gunner->GetReloadDuration(), false);
	
	return return_value;
}