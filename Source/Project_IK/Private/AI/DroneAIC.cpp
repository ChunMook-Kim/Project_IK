/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Source file for Drone AIC.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/DroneAIC.h"

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
