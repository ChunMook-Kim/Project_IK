/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.08.2024
Summary : Header file for Passive Gunner Enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Characters/PassiveEnemy.h"
#include "Interfaces/GunnerInterface.h"
#include "PassiveGunnerEnemy.generated.h"


class UWeaponMechanics;
UCLASS()
class PROJECT_IK_API APassiveGunnerEnemy : public APassiveEnemy, public IGunnerInterface
{
	GENERATED_BODY()
public:
	APassiveGunnerEnemy();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	virtual void Die() override;
	
	virtual void Reload() override;
	virtual void WaitForDuration() override;
	virtual void FinishReload() override;

	virtual void StartFire(AActor* target) override;
	virtual void OnFire(AActor* target) override;
	virtual void FinishFire() override;
	
	virtual bool IsMagazineEmpty() const override;
	virtual float GetFireInterval() const override;
	virtual float GetReloadDuration() const override;

	virtual void OnStunned() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UWeaponMechanics* weapon_mechanics_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UAnimMontage* fire_montage_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UAnimMontage* reload_montage_;

	UPROPERTY(Transient)
	FTimerHandle fire_timer_;
};
