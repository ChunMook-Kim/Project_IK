// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DroneMechanics.h"
#include "Abilities/PassiveSkill.h"

// Sets default values for this component's properties
UDroneMechanics::UDroneMechanics()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDroneMechanics::BeginPlay()
{
	Super::BeginPlay();
	if(plug_in_class_) plugin_ = Cast<ADronePlugIn>(GetWorld()->SpawnActor(plug_in_class_));
}

void UDroneMechanics::Initialize(AActor* hero)
{
	hero_ref_ = hero;
	if(plugin_) plugin_->Initialize(hero_ref_);
}

void UDroneMechanics::ActivateDronePlugin()
{
	if(plugin_ != nullptr)
	{
		plugin_->StartPassiveSkill();
	}
}

float UDroneMechanics::GetHoldTime() const
{
	return plugin_->GetHoldTime();
}

void UDroneMechanics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UDroneMechanics::IsDronePluginAvailable() const
{
	return plugin_->IsPassiveAvailable();
}

// void UDroneMechanics::AddPlugIn(int idx, UClass* plugin_type)
// {
// 	if(idx < 0 || idx >= plugins_.Num())
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("Out of index!"));
// 	}
// 	else if(plugin_type == nullptr)
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("Plug_in class is empty!"));
// 	}
// 	else
// 	{
// 		if(plugin_amount_ < max_amount_)
// 		{
// 			plugins_[idx] = Cast<ADronePlugIn>(GetWorld()->SpawnActor(plugin_type));
// 		}
// 	}
// }
//
// void UDroneMechanics::RemovePlugIn(int idx)
// {
// 	plugins_.RemoveAt(idx);
// }
