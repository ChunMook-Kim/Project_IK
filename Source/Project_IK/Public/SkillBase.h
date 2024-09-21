/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for Skill base class.
					It will be used like a pure virtual class. A skill class will derived it.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API USkillBase : public UObject
{
	GENERATED_BODY()
	
public:
	USkillBase();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ActivateSkill();

	virtual void ActivateSkill_Implementation() PURE_VIRTUAL(USkillBase::ActivateSkill_Implementation, ;);

protected:
	UPROPERTY(VisibleAnywhere)
	float cost_;
};
