/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Source file for Test skill class.
					The first skill class to test it.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/MyTestSkill.h"

#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

UMyTestSkill::UMyTestSkill()
	: Super::USkillBase(10.f)
{
}

bool UMyTestSkill::ActivateSkill_Implementation(const FTargetData& TargetData)
{
	const bool is_energy_enough = SpendCost();
	if (is_energy_enough == false)
	{
		return false;	
	}

	UE_LOG(LogTemp, Warning, TEXT("Skill executed in derived class! %s"), *TargetData.target_location_.ToString());
	for (int32 i = 0; i < TargetData.target_actors_.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected %ith actor name: %s"), i, *TargetData.target_actors_[i]->GetName());
	}
	return true;
}
