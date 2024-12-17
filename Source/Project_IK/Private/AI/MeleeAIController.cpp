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
	stun_state_key_name_ = TEXT("StunState");
}

void AMeleeAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(timer_handle_);
	Super::EndPlay(EndPlayReason);
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

void AMeleeAIController::GetStunned(float duration)
{
	SetUnitState(EUnitState::Stunned);
	SetStunState(EStunState::BeginStun);
	GetWorldTimerManager().SetTimer(timer_handle_,this, &AMeleeAIController::FinishStun, duration, false);
}

void AMeleeAIController::FinishStun()
{
	SetStunState(EStunState::FinishStun);
}

void AMeleeAIController::SetUnitState(EUnitState new_state)
{
	GetBlackboardComponent()->SetValueAsEnum(unit_state_key_name_, static_cast<uint8>(new_state));
}

void AMeleeAIController::SetStunState(EStunState new_state)
{
	GetBlackboardComponent()->SetValueAsEnum(stun_state_key_name_, static_cast<uint8>(new_state));
}

void AMeleeAIController::OnDie()
{
	
}