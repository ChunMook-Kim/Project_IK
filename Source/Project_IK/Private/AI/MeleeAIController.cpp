/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.08.2024
Summary : Source file for Melee AI Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/MeleeAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

AMeleeAIController::AMeleeAIController()
{
	target_class_key_name_ = TEXT("TargetClass");
	unit_state_key_name_ = TEXT("UnitState");
}

void AMeleeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(behavior_tree_)
	{
		RunBehaviorTree(behavior_tree_);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BlackBoard isn't exist!"));
	}
	if(GetBlackboardComponent()->IsValidKey(GetBlackboardComponent()->GetKeyID(target_class_key_name_)))
	{
		GetBlackboardComponent()->SetValueAsClass(target_class_key_name_, target_class_);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Target class key name is wrong!"));
	}
	if(GetBlackboardComponent()->IsValidKey(GetBlackboardComponent()->GetKeyID(unit_state_key_name_)))
	{
		GetBlackboardComponent()->SetValueAsEnum(unit_state_key_name_, static_cast<uint8>(EUnitState::Forwarding));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("unit state enum key name is wrong!"));
	}
}

void AMeleeAIController::SetUnitState(EUnitState new_state)
{
	GetBlackboardComponent()->SetValueAsEnum(unit_state_key_name_, static_cast<uint8>(new_state));
}

void AMeleeAIController::OnDie()
{
	
}
