/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.05.2024
Summary : Source file for IsArrivedFirePosition decorator.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Decorator_IsArrivedFirePosition.h"

#include "AIController.h"
#include "Components/CharacterStatComponent.h"
#include "Characters/Unit.h"
#include "BehaviorTree/BlackboardComponent.h"

UDecorator_IsArrivedFirePosition::UDecorator_IsArrivedFirePosition()
{
	NodeName = TEXT("IsArrivedFirePosition");
}

bool UDecorator_IsArrivedFirePosition::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AUnit* casted_unit = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* attack_target = Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName));

	if (blackboard->IsValidKey(owned_cover_key_.GetSelectedKeyID()))
	{
		//만약 선택된 엄폐물이 있다면 엄폐물로 가야 한다.
		AActor* cover_actor = Cast<AActor>(blackboard->GetValueAsObject(owned_cover_key_.SelectedKeyName));
		float cover_owner_dist = FVector::Dist2D(cover_actor->GetActorLocation(), casted_unit->GetActorLocation());
		if(cover_owner_dist <= 1.0)
		{
			return true;
		}
	}
	else
	{
		//만약 선택된 엄폐물이 없다면, 적이 사거리에 닫을 때 까지 가야 한다.
		if(attack_target)
		{
			float owner_enemy_dist = FVector::Dist2D(attack_target->GetActorLocation(), casted_unit->GetActorLocation());
			float fire_range = casted_unit->GetCharacterStat()->GetFireRange();
			if(owner_enemy_dist <= fire_range)
			{
				return true;
			}
		}
	}
	return false;
}
