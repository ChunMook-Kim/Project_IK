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

public:
	virtual void Die() override;
	
	virtual void Reload() override;
	virtual void Fire(AActor* target) override;
	
	virtual void ActivatePassive() override;
	virtual bool IsPassiveAvailable() override;
	virtual float GetPassiveHoldTime() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	USkillContainer* skill_container_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UWeaponMechanics* weapon_mechanics_;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveSkillGunner", meta = (AllowPrivateAccess = "true"))
	UPassiveMechanics* passive_mechanics_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UAnimMontage* fire_montage_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true", BindWidget))
	UAnimMontage* reload_montage_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true", BindWidget))
	UClass* drone_bp_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero", meta = (AllowPrivateAccess = "true"))
	USphereComponent* drone_location_;

	AActor* drone_;
};
