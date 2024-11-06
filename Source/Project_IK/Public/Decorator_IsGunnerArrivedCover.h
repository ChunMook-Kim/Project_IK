// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Decorator_IsGunnerArrivedCover.generated.h"

UCLASS()
class PROJECT_IK_API UDecorator_IsGunnerArrivedCover : public UBTDecorator
{
	GENERATED_BODY()

public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
		FBlackboardKeySelector owned_cover_key_;
};
