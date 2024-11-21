/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Source file for unit arrived cover check decorator.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "AI/Decorator_IsGunnerArrivedCover.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UDecorator_IsGunnerArrivedCover::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	APawn* casted_gunner = OwnerComp.GetAIOwner()->GetPawn();
	AActor* cover_actor = Cast<AActor>(blackboard->GetValueAsObject(owned_cover_key_.SelectedKeyName));
	float cover_owner_dist = FVector::Dist2D(cover_actor->GetActorLocation(), casted_gunner->GetActorLocation());
	if(cover_owner_dist <= 50.0)
	{
		return true;
	}
	return false;
}