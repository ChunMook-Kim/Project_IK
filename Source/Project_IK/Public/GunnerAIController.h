// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GunnerAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AGunnerAIController : public AAIController
{
	GENERATED_BODY()
public:
	void OnDie();
	virtual void OnPossess(APawn* InPawn) override;

private:
	UBehaviorTree* tree_;
	UClass* target_class_;
	FName target_class_name_;
	FName owned_cover_name_;
};
