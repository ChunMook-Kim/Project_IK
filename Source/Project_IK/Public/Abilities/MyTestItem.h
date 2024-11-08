/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.20.2024
Summary : Source file for MyTestItem.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "MyTestItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UMyTestItem : public USkillBase
{
	GENERATED_BODY()

public:
	UMyTestItem();

	virtual bool ActivateSkill_Implementation(const FTargetData& TargetData) override;

private:
	
};
