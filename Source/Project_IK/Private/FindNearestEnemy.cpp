// Fill out your copyright notice in the Description page of Project Settings.


#include "FindNearestEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Class.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UFindNearestEnemy::UFindNearestEnemy() 
{
	NodeName = "FindNearestEnemy";
	Interval = 0.05f;
	RandomDeviation = 0.f;

	target_class_key_.AddClassFilter(this, GET_MEMBER_NAME_CHECKED(UFindNearestEnemy, BlackboardKey), AActor::StaticClass());
	target_enemy_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindNearestEnemy, BlackboardKey), AActor::StaticClass());
}

void UFindNearestEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	const UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AActor* owner_actor = OwnerComp.GetOwner();
	UWorld* world = GetWorld();

	if (blackboard) 
	{
		//TODO: Gunner역시 C++로 구현한 다음, Object를 Gunner로 Cast해야 한다.
		UObject* target_enemy = blackboard->GetValueAsObject(target_enemy_key_.SelectedKeyName);
		UClass* target_class = blackboard->GetValueAsClass(target_class_key_.SelectedKeyName);

		//if (target_class && target_enemy) {
		//	TArray<FOverlapResult> OverlapResults;
		//	FCollisionQueryParams CollisionQueryParam(NAME_None, false, owner_actor);
		//	//TODO: 여기다 class를 넣어야 함.
		//	FCollisionObjectQueryParams query_params(ECollisionChannel::ECC_WorldStatic);
		//	bool result = world->OverlapMultiByObjectType(
		//		OverlapResults,
		//		owner_actor->GetActorLocation(),
		//		FQuat::Identity,
		//		query_params,
		//		FCollisionShape::MakeSphere(/*Gunner->sightRange*/0),
		//		CollisionQueryParam
		//	);
		//}
		//TODO: 가장 가까운 적을 다시 blackboard에 set해야 한다.
	}
}