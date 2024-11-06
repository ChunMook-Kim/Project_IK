// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorator_IsGunnerArrivedCover.h"

#include "AIController.h"
#include "CharacterStatComponent.h"
#include "Gunner.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UDecorator_IsGunnerArrivedCover::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AGunner* casted_gunner = Cast<AGunner>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* cover_actor = Cast<AActor>(blackboard->GetValueAsObject(owned_cover_key_.SelectedKeyName));
	float cover_owner_dist = FVector::Dist2D(cover_actor->GetActorLocation(), casted_gunner->GetActorLocation());
	if(cover_owner_dist <= 50.0)
	{
		return true;
	}
	return false;
}