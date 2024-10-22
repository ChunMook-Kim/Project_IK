/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.20.2024
Summary : Source file for MyTestItem.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "MyTestItem.h"

UMyTestItem::UMyTestItem()
	: Super::USkillBase(0.f)
{
}

bool UMyTestItem::ActivateSkill_Implementation(const FTargetData& TargetData)
{
	UE_LOG(LogTemp, Warning, TEXT("MyTestItem has successfully activated!"));
	return true;
}
