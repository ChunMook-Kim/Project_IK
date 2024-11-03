// Fill out your copyright notice in the Description page of Project Settings.

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
	virtual void Fire();
	virtual void GetDamage(int damage_amount);

private:
	UCharacterStatComponent* character_stat_component_;
	USkillContainer* skill_container_;
	UWeaponMechanics* weapon_mechanics_;
	UWidgetComponent* hp_UI_;
};
