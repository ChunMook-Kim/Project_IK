/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Gunner AI Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "GunnerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Cover.h"

void AGunnerAIController::OnPossess(APawn* InPawn)
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
}

void AGunnerAIController::OnDie()
{
	UObject* cover = GetBlackboardComponent()->GetValueAsObject(owned_cover_key_name_);
	if(cover != nullptr)
	{
		ACover* casted_cover = Cast<ACover>(cover);
		casted_cover->SetIsBroken(false);
		casted_cover->SetCoveringOwner(false);
	}
}