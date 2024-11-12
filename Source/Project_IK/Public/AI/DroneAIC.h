// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DroneAIC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API ADroneAIC : public AAIController
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* behavior_tree_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true"))
	UClass* target_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true"))
	FName target_class_key_name_;
};
