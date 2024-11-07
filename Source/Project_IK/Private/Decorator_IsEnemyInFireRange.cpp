// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorator_IsEnemyInFireRange.h"

#include "AIController.h"
#include "CharacterStatComponent.h"
#include "Gunner.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UDecorator_IsEnemyInFireRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AGunner* casted_gunner = Cast<AGunner>(OwnerComp.GetAIOwner()->GetPawn());

	if (AActor* attack_target = Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName));)
	{
		float owner_enemy_dist = FVector::Dist2D(attack_target->GetActorLocation(), casted_gunner->GetActorLocation());
		float fire_range = casted_gunner->GetCharacterStatComponent()->GetFireRange();
		if (owner_enemy_dist < fire_range)
		{
			return true;
		}
	}
	return false;
}