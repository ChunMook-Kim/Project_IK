/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Source file for Enemy in Fire range check decorator.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "AI/Decorator_IsEnemyInFireRange.h"

#include "AIController.h"
#include "Components/CharacterStatComponent.h"
#include "Characters/Gunner.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UDecorator_IsEnemyInFireRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AGunner* casted_gunner = Cast<AGunner>(OwnerComp.GetAIOwner()->GetPawn());

	if (AActor* attack_target = Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName)))
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