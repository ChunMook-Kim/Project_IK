/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.05.2024
Summary : Source file for Find best cover node.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Service_FindBestCover.h"

#include "AIController.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"
#include "Environments/Cover.h"

UService_FindBestCover::UService_FindBestCover()
{
	NodeName = "FindBestCover";
	Interval = 0.001f;
	RandomDeviation = 0.f;

	owned_cover_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_FindBestCover, owned_cover_key_), UObject::StaticClass());
	attack_target_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_FindBestCover, attack_target_key_), UObject::StaticClass());
}

void UService_FindBestCover::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

	AActor* cover = Cast<AActor>(blackboard->GetValueAsObject(owned_cover_key_.SelectedKeyName));
	AActor* attack_target = Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName));
	
	//현재 소유한 cover가 없어야만 새로운 cover를 찾아야 함.
	if(cover == nullptr)
	{
		//cover의 계산에는 적의 위치가 필요함.
		if(attack_target)
		{
			AUnit* casted_gunner = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn());
			FVector attack_target_pos = attack_target->GetActorLocation();
			
			TArray<FOverlapResult> overlap_results;
			FCollisionQueryParams CollisionQueryParam(NAME_None, false, casted_gunner);
			
			bool result = GetWorld()->OverlapMultiByChannel(
			overlap_results,
			casted_gunner->GetActorLocation(),
			FQuat::Identity,
			ECollisionChannel::ECC_WorldStatic,
			FCollisionShape::MakeSphere(casted_gunner->GetCharacterStat()->GetSightRange()),
			CollisionQueryParam
			);
			
			ACover* best_cover = nullptr;
			for(const auto& elem : overlap_results)
			{
				if(ACover* casted_cover = Cast<ACover>(elem.GetActor()))
				{
					//만약 cover가 부서져있거나 이미 다른 주인이 있다면 넘어간다.
					if(casted_cover->IsBroken() || casted_cover->HasCoveringOwner()) continue;
					
					FVector cover_pos = elem.GetActor()->GetActorLocation();
					//만약 엄폐물에서의 위치와 가장 가까운 적의 거리가 사거리 보다 길다면 넘어간다.
					if(FVector::Dist2D(cover_pos, attack_target_pos) >
						casted_gunner->GetCharacterStat()->GetFireRange()) continue;

					FVector cover_to_target = attack_target_pos - cover_pos;
					cover_to_target.Normalize();
					
					float angle_similarity = FVector::DotProduct(cover_to_target, casted_cover->GetActorForwardVector());
					if(angle_similarity < 0.5) continue;
					
					best_cover = casted_cover;
				}
			}
			if(best_cover)
			{
				best_cover->SetCoveringOwner(true);
				blackboard->SetValueAsObject(owned_cover_key_.SelectedKeyName, best_cover);
			}
		}
	}
}
