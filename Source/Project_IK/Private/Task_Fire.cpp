#include "Task_Fire.h"

#include "Gunner.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UTask_Fire::UTask_Fire(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Fire";
	bTickIntervals = true;
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UTask_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AGunner* casted_gunner = Cast<AGunner>(OwnerComp.GetAIOwner()->GetPawn());
	if(	AActor* casted_target = Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName)))
	{
		casted_gunner->Fire(casted_target);
	}
	
	SetNextTickTime(NodeMemory, casted_gunner->GetFireInterval());
	
	return EBTNodeResult::InProgress;
}

void UTask_Fire::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Using the SetNextTickTime in ExecuteTask we are certain we are only getting ticked when the wait is finished
	ensure(GetSpecialNodeMemory<FBTTaskMemory>(NodeMemory)->NextTickRemainingTime <= 0.f);

	// continue execution from this node
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

