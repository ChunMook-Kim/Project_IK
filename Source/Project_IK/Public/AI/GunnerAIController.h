/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Gunner AI Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* behavior_tree_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true", AllowedClass = "HeroBase, EnemyBase"))
	UClass* target_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true"))
	FName target_class_key_name_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true"))
	FName owned_cover_key_name_;
};
