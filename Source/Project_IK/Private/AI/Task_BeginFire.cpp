/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Source file for BeginFire Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_BeginFire.h"

#include "AIController.h"
#include "AI/GunnerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WeaponMechanics.h"

UTask_BeginFire::UTask_BeginFire()
{
	NodeName = "Begin Fire";
}

EBTNodeResult::Type UTask_BeginFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

	auto casted_pawn = OwnerComp.GetAIOwner()->GetPawn();
	auto component = casted_pawn->GetComponentByClass(UWeaponMechanics::StaticClass()); 
	if(auto casted_component = Cast<UWeaponMechanics>(component))
	{
		if(	AActor* casted_target = Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName)))
		{
			casted_component->BeginFire(casted_target);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
