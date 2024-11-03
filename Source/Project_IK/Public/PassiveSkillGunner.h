// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gunner.h"
#include "PassiveSkillGunner.generated.h"

class UPassiveMechanics;
/**
 * 
 */
UCLASS()
class PROJECT_IK_API APassiveSkillGunner : public AGunner
{
	GENERATED_BODY()

public:
	APassiveSkillGunner();

	UPassiveMechanics* passive_mechanics_;
};
