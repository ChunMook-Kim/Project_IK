/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.08.2024
Summary : Header file for Passive Enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Characters/EnemyBase.h"
#include "Interfaces/PassiveCaster.h"
#include "PassiveEnemy.generated.h"

class UPassiveMechanics;
UCLASS()
class PROJECT_IK_API APassiveEnemy : public AEnemyBase, public IPassiveCaster
{
	GENERATED_BODY()

public:
	APassiveEnemy();
	virtual void Die() override;
	
	virtual bool IsPassiveAvailable() override;
	virtual float GetPassiveHoldTime() override;

	virtual void ActivatePassive() override;
	virtual void FinishPassiveHoldTime() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UPassiveMechanics* passive_mechanics_;

	FTimerHandle passive_hold_timer_;
};
