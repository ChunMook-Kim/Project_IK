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
#include "Managers/EnumCluster.h"
#include "MeleeAIController.generated.h"

UCLASS()
class PROJECT_IK_API AMeleeAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMeleeAIController();
	virtual void OnDie();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(Blueprintable, BlueprintCallable, Category = "AI")
	virtual void GetStunned(float duration);
	virtual void FinishStun();
	
	UFUNCTION(Blueprintable)
	void SetUnitState(EUnitState new_state);

	UFUNCTION(Blueprintable)
	void SetStunState(EStunState new_state);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MeleeAI", meta = (AllowPrivateAccess = "true", BindWidget))
	UBehaviorTree* behavior_tree_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MeleeAI", meta = (AllowPrivateAccess = "true", AllowedClass = "HeroBase, EnemyBase", BindWidget))
	UClass* target_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MeleeAI", meta = (AllowPrivateAccess = "true", BindWidget))
	FName target_class_key_name_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MeleeAI", meta = (AllowPrivateAccess = "true", BindWidget))
	FName unit_state_key_name_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MeleeAI", meta = (AllowPrivateAccess = "true", BindWidget))
	FName stun_state_key_name_;

private:
	FTimerHandle timer_handle_;
};
