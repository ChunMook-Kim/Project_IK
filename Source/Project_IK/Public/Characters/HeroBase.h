/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Header file for hero base. Every hero should inherit this class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "Interfaces/GunnerInterface.h"
#include "Interfaces/PassiveCaster.h"
#include "CoreMinimal.h"
#include "Characters/Unit.h"
#include "HeroBase.generated.h"

class ADrone;
class USphereComponent;
class UPassiveMechanics;
class UWeaponMechanics;
class USkillContainer;

UCLASS()
class PROJECT_IK_API AHeroBase : public AUnit, public IGunnerInterface, public IPassiveCaster
{
	GENERATED_BODY()
public:
	AHeroBase();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Initialize();
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

	virtual void ActivatePassive() override;
	virtual bool IsPassiveAvailable() override;
	virtual void WaitForHoldTime() override;
	virtual void FinishPassive() override;
	virtual float GetPassiveHoldTime() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	USkillContainer* skill_container_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UWeaponMechanics* weapon_mechanics_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UPassiveMechanics* passive_mechanics_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UAnimMontage* fire_montage_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UAnimMontage* reload_montage_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true", AllowedClass = "Drone", BindWidget))
	UClass* drone_bp_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	USphereComponent* drone_location_;

	UPROPERTY(Transient)
	FTimerHandle fire_timer_;

	ADrone* drone_;
};
