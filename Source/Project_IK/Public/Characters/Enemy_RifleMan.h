/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Header file for rifle man enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Characters/EnemyBase.h"
#include "Enemy_RifleMan.generated.h"

class UWeaponMechanics;
UCLASS()
class PROJECT_IK_API AEnemy_RifleMan : public AEnemyBase
{
	GENERATED_BODY()
public:
	AEnemy_RifleMan();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnStunned() override;
	virtual void Die() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UWeaponMechanics* weapon_mechanics_;
};
