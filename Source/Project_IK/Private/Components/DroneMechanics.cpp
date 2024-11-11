// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DroneMechanics.h"
#include "Abilities/PassiveSkill.h"

// Sets default values for this component's properties
UDroneMechanics::UDroneMechanics()
{
	PrimaryComponentTick.bCanEverTick = true;
	plugin_amount = 0;
	
	plugins_.Reserve(max_amount_);
}


// Called when the game starts
void UDroneMechanics::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UDroneMechanics::AddPlugIn(int idx, UClass* plugin_type)
{
	if(idx < 0 || idx >= plugins_.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Out of index!"));
	}
	else if(plugin_type == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Plug_in class is empty!"));
	}
	else
	{
		auto spawned_plug_in = Cast<ADronePlugIn>(GetWorld()->SpawnActor(plugin_type));
		if(plugin_amount < max_amount_)
		{
			plugins_[idx] = spawned_plug_in;
		}
	}
}

void UDroneMechanics::RemovePlugIn(int idx)
{
	plugins_.RemoveAt(idx);
}

// Called every frame
void UDroneMechanics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

