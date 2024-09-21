/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Source file for Test skill class.
					The first skill class to test it.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "MyTestSkill.h"

UMyTestSkill::UMyTestSkill()
	: Super::USkillBase()
{
	cost_ = 0;
}

void UMyTestSkill::ActivateSkill_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Skill executed in derived class!"));
}
