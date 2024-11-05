/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.05.2024
Summary : Header file for Gunner.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gunner.generated.h"

class UCharacterStatComponent;
class USkillContainer;
class UWeaponMechanics;
class UWidgetComponent;

UCLASS()
class PROJECT_IK_API AGunner : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGunner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void OnDie();
	virtual void Reload();
	virtual void Fire(AActor* target);
	virtual void GetDamage(int damage_amount);

	UCharacterStatComponent* GetCharacterStatComponent() const;
	void SetCharacterStatComponent(UCharacterStatComponent* Character_Stat_Component);
	FVector GetForwardDir() const;
	void SetForwardDir(const FVector& Forward_Dir);
	bool IsMegazineEmpty() const;
	float GetReloadDuration() const;
	float GetFireInterval() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true"))
	UCharacterStatComponent* character_stat_component_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true"))
	USkillContainer* skill_container_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true"))
	UWeaponMechanics* weapon_mechanics_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* hp_UI_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* fire_montage_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* reload_montage_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gunner", meta = (AllowPrivateAccess = "true"))
	FVector forward_dir_;
};
