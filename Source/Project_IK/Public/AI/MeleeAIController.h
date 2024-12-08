/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.08.2024
Summary : Header file for Melee AI Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MeleeAIController.generated.h"

UCLASS()
class PROJECT_IK_API AMeleeAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMeleeAIController();
	virtual void OnDie();
	virtual void OnPossess(APawn* InPawn) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true", BindWidget))
	UBehaviorTree* behavior_tree_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true", AllowedClass = "HeroBase, EnemyBase", BindWidget))
	UClass* target_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true", BindWidget))
	FName target_class_key_name_;
};
