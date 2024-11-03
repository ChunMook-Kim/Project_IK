// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PassiveSkill.h"
#include "HealthBurst.generated.h"

class AGunner;
/**
 * 
 */
UCLASS()
class PROJECT_IK_API AHealthBurst : public APassiveSkill
{
	GENERATED_BODY()
	virtual void Tick(float DeltaSeconds) override;

private:
	float heal_amount_ = 10.f;
	AGunner* gunner_caster_ = nullptr;
};
