/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.05.2024
Summary : Source file for Find Nearest Enemy service node.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Service_FindNearestEnemy.h"

#include "AIController.h"
#include "CharacterStatComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Class.h"
#include "Gunner.h"
#include "Engine/OverlapResult.h"

UService_FindNearestEnemy::UService_FindNearestEnemy()
{
	NodeName = "FindNearestEnemy";
	Interval = 0.05f;
	RandomDeviation = 0.f;

	target_class_key_.AddClassFilter(this, GET_MEMBER_NAME_CHECKED(UService_FindNearestEnemy, target_class_key_), UObject::StaticClass());
	attack_target_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_FindNearestEnemy, attack_target_key_), UObject::StaticClass());
}

void UService_FindNearestEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AGunner* casted_gunner = Cast<AGunner>(OwnerComp.GetAIOwner()->GetPawn());
	UWorld* world = GetWorld();

	float min_distance = TNumericLimits<float>::Max();
	if (blackboard) 
	{
		if (UClass* target_class = blackboard->GetValueAsClass(target_class_key_.SelectedKeyName)) {
			//TODO: 확실히 C++에서 Target Class만 검사하는 방법을 알아야 함. 만약 없다면 ECC를 새로 생성해야 함.
			TArray<FOverlapResult> overlap_results;
			FCollisionQueryParams CollisionQueryParam(NAME_None, false, casted_gunner);
			ECollisionChannel channel(ECC_Pawn);

			if(IsValid(casted_gunner))
			{
				bool overlap_result = world->OverlapMultiByChannel(
			overlap_results,
			casted_gunner->GetActorLocation(),
			FQuat::Identity,
			channel,
			FCollisionShape::MakeSphere(casted_gunner->GetCharacterStatComponent()->GetSightRange()),
			CollisionQueryParam
				);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to cast owner to gunner!"));
			}
			
			AActor* nearest_actor = nullptr;
			for(const auto& elem : overlap_results)
			{
				if(elem.GetActor()->IsA(target_class))
				{
					FVector owner_pos = casted_gunner->GetActorLocation();
					FVector target_pos = elem.GetActor()->GetActorLocation();
					float cur_distance = FVector::DistSquared2D(owner_pos, target_pos);
					if(cur_distance < min_distance)
					{
						nearest_actor = elem.GetActor();
						min_distance = cur_distance;
					}
				}
			}
			if(nearest_actor != nullptr)
			{
				blackboard->SetValueAsObject(attack_target_key_.SelectedKeyName, nearest_actor);
			}
		}
	}
}
