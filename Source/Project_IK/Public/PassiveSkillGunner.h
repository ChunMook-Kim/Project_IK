/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Gunner PassiveSkill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
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

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover", meta = (AllowPrivateAccess = "true"))
	UPassiveMechanics* passive_mechanics_;
};
