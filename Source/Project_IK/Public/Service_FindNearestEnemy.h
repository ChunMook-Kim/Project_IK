// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Service_FindNearestEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UService_FindNearestEnemy : public UBTService
{
	GENERATED_BODY()

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	UService_FindNearestEnemy();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthBurst", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector target_class_key_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthBurst", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector attack_target_key_;
};
