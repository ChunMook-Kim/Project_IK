// Fill out your copyright notice in the Description page of Project Settings.


#include "GunnerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Cover.h"

void AGunnerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(tree_);
	GetBlackboardComponent()->SetValueAsClass(target_class_name_, target_class_);
}

void AGunnerAIController::OnDie()
{
	UObject* cover = GetBlackboardComponent()->GetValueAsObject(owned_cover_name_);
	if(cover != nullptr)
	{
		Cast<ACover>(cover)->SetIsBroken(false);
	}
}