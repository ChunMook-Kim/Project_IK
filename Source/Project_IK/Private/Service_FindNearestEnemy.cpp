// Fill out your copyright notice in the Description page of Project Settings.


#include "Service_FindNearestEnemy.h"

#include "CharacterStatComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Class.h"
#include "Gunner.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
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
	AActor* owner_actor = OwnerComp.GetOwner();
	UWorld* world = GetWorld();

	float min_distance = TNumericLimits<float>::Max();
	if (blackboard) 
	{
		UClass* target_class = blackboard->GetValueAsClass(target_class_key_.SelectedKeyName);
		if (target_class) {
			//TODO: 확실히 C++에서 Target Class만 검사하는 방법을 알아야 함. 만약 없다면 ECC를 새로 생성해야 함.
			TArray<FOverlapResult> overlap_results;
			FCollisionQueryParams CollisionQueryParam(NAME_None, false, owner_actor);
			ECollisionChannel channel(ECC_Pawn);
			AGunner* casted_gunner = Cast<AGunner>(owner_actor);
			if(IsValid(casted_gunner))
			{
				bool result = world->OverlapMultiByChannel(
				overlap_results,
				owner_actor->GetActorLocation(),
				FQuat::Identity,
				channel,
				FCollisionShape::MakeSphere(casted_gunner->GetCharacterStatComponent()->GetSightRange()),
				CollisionQueryParam
				);
			}
			AActor* nearest_actor = nullptr;
			for(const auto& elem : overlap_results)
			{
				if(elem.GetActor()->IsA(target_class))
				{
					FVector owner_pos = owner_actor->GetActorLocation();
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
