// Fill out your copyright notice in the Description page of Project Settings.


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
