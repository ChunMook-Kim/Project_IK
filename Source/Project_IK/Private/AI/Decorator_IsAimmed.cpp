﻿/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Source file for Aimmed check decorator.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Decorator_IsAimmed.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UDecorator_IsAimmed::UDecorator_IsAimmed()
{
	NodeName = "IsAimmed";
}

bool UDecorator_IsAimmed::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AAIController* controller = OwnerComp.GetAIOwner();
	APawn* casted_pawn = controller->GetPawn();
	AActor* attack_target = Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName));

	if(attack_target)
	{
		//이동사격이 가능하지 않는 한, 조준 시에는 반드시 MoveTo가 멈춰야 한다.
		controller->StopMovement();
		FVector owner_to_target = attack_target->GetActorLocation() - casted_pawn->GetActorLocation();
		owner_to_target.Normalize();
		return FVector::DotProduct(owner_to_target, casted_pawn->GetActorForwardVector()) >= 0.9999;
	}
	return false;
}
