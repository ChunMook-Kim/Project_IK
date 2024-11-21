/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Passive Mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/PassiveMechanics.h"
#include "Abilities/PassiveSkill.h"

// Sets default values for this component's properties
UPassiveMechanics::UPassiveMechanics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPassiveMechanics::BeginPlay()
{
	Super::BeginPlay();
	if(passive_class_)
	{
		passive_ref_ = Cast<APassiveSkill>(GetWorld()->SpawnActor(passive_class_));
		passive_ref_->Initialize(GetOwner());
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("PassiveMechanics::BeginPlay Error. Passive class should be setted"));
	}
	
}

void UPassiveMechanics::ActivePassiveSkill()
{
	passive_ref_->StartPassiveSkill();
}

//Passive skill의 Finish Passive Skill은 Passive Skill의 마지막 틱에 자동으로 호출된다.
void UPassiveMechanics::FinishPassiveSkill()
{
	passive_ref_->FinishPassiveSkill();
}

bool UPassiveMechanics::IsPassiveAvailable() const
{
	return passive_ref_->IsPassiveAvailable();
}

float UPassiveMechanics::GetHoldTime() const
{
	return passive_ref_->GetHoldTime();
}
