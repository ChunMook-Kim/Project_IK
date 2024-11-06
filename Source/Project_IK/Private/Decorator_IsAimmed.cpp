// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorator_IsAimmed.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UDecorator_IsAimmed::UDecorator_IsAimmed()
{
	NodeName = "IsAimmed";
}

bool UDecorator_IsAimmed::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AAIController* controller = OwnerComp.GetAIOwner();
	APawn* casted_pawn = controller->GetPawn();
	AActor* attack_target = Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName));

	//이동사격이 가능하지 않는 한, 조준 시에는 반드시 MoveTo가 멈춰야 한다.
	controller->StopMovement();
	FVector owner_to_target = attack_target->GetActorLocation() - casted_pawn->GetActorLocation();
	owner_to_target.Normalize();
	return FVector::DotProduct(owner_to_target, casted_pawn->GetActorForwardVector()) >= 0.9999;
}
