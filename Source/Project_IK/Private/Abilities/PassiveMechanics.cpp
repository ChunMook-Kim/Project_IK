/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Passive Mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/PassiveMechanics.h"

#include "AIController.h"
#include "Abilities/PassiveSkill.h"
#include "AI/PassiveGunnerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

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

void UPassiveMechanics::ActivatePassiveSkill()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Passive"));

	passive_ref_->StartPassiveSkill();
	if(auto ai_controller = Cast<APassiveGunnerAIController>(Cast<APawn>(GetOwner())->Controller))
	{
		ai_controller->SetPassiveState(EPassiveState::WaitingHoldTime);
	}
}

void UPassiveMechanics::WaitingHoldTime()
{
	if(GetWorld()->GetTimerManager().IsTimerActive(hold_time_handle_) == false)
	{
		if(GetHoldTime() == 0.f)
		{
			FinishHoldTime();
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(hold_time_handle_, this, &UPassiveMechanics::FinishHoldTime, GetHoldTime());
		}
	}
}

void UPassiveMechanics::FinishHoldTime()
{
	GetWorld()->GetTimerManager().ClearTimer(hold_time_handle_);
	if(auto ai_controller = Cast<APassiveGunnerAIController>(Cast<APawn>(GetOwner())->Controller))
	{
		UE_LOG(LogTemp, Warning, TEXT("Finish Hold Time"));
		ai_controller->SetPassiveState(EPassiveState::BeginPassive);
	}
}

bool UPassiveMechanics::IsPassiveAvailable() const
{
	return passive_ref_->IsPassiveAvailable();
}

float UPassiveMechanics::GetHoldTime() const
{
	return passive_ref_->GetHoldTime();
}