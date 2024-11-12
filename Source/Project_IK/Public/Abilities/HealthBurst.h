/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for HealthBurst Passive Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
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
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthBurst", meta = (AllowPrivateAccess = "true"))
	float heal_amount_ = 100.f;
	
	AGunner* gunner_caster_ = nullptr;
};
