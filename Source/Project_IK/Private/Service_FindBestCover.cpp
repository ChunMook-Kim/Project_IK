/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.05.2024
Summary : Source file for Find best cover node.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Service_FindBestCover.h"
#include "Gunner.h"
#include "CharacterStatComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"

UService_FindBestCover::UService_FindBestCover()
{
	NodeName = "FindBestCover";
	Interval = 0.05f;
	RandomDeviation = 0.f;

	owned_cover_key_.AddClassFilter(this, GET_MEMBER_NAME_CHECKED(UService_FindBestCover, owned_cover_key_), UObject::StaticClass());
	attack_target_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_FindBestCover, attack_target_key_), UObject::StaticClass());
}

void UService_FindBestCover::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	//현재 소유한 cover가 없어야만 새로운 cover를 찾아야 함.
	if(blackboard->IsValidKey(owned_cover_key_.GetSelectedKeyID()) == false)
	{
		//cover의 계산에는 적의 위치가 필요함.
		if(blackboard->IsValidKey(attack_target_key_.GetSelectedKeyID()))
		{
			AGunner* casted_gunner = Cast<AGunner>(OwnerComp.GetOwner());
			TArray<FOverlapResult> overlap_results;
			FCollisionQueryParams CollisionQueryParam(NAME_None, false, casted_gunner);
			ECollisionChannel channel(ECC_WorldStatic);
			
			bool result = GetWorld()->OverlapMultiByChannel(
			overlap_results,
			casted_gunner->GetActorLocation(),
			FQuat::Identity,
			channel,
			FCollisionShape::MakeSphere(casted_gunner->GetCharacterStatComponent()->GetSightRange()),
			CollisionQueryParam
			);
			
			AActor* best_cover = nullptr;
		}
	}
}
