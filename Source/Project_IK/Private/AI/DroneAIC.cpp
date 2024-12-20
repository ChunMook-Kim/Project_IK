/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Source file for Drone AIC.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/DroneAIC.h"

#include "BehaviorTree/BlackboardComponent.h"

ADroneAIC::ADroneAIC()
{
	dp_state_key_name_= TEXT("DPState");
	drone_state_key_name_= TEXT("DroneState");
	target_class_key_name_ = TEXT("TargetClass");
}

void ADroneAIC::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(behavior_tree_)
	{
		RunBehaviorTree(behavior_tree_);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tree isn't exist!"));
	}
}

void ADroneAIC::BeginPlay()
{
	Super::BeginPlay();
	if(behavior_tree_)
	{
		RunBehaviorTree(behavior_tree_);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tree isn't exist!"));
	}
}

void ADroneAIC::SetDPState(EDPState new_state)
{
	GetBlackboardComponent()->SetValueAsEnum(dp_state_key_name_, static_cast<uint8>(new_state));
}

void ADroneAIC::SetDroneState(EDroneState new_state)
{
	GetBlackboardComponent()->SetValueAsEnum(drone_state_key_name_, static_cast<uint8>(new_state));
}
