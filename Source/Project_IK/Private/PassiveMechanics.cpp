// Fill out your copyright notice in the Description page of Project Settings.

#include "PassiveMechanics.h"
#include "PassiveSkill.h"

// Sets default values for this component's properties
UPassiveMechanics::UPassiveMechanics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPassiveMechanics::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UPassiveMechanics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (is_activated_)
	{
		duration_ -= DeltaTime;
		if(duration_ <= 0) cool_down_ -= DeltaTime;
		if(cool_down_ <= 0) is_activated_ = false;
	}
}

void UPassiveMechanics::ActivePassiveSkill()
{
	auto spawned_skill = Cast<APassiveSkill>(GetWorld()->SpawnActor(passive_class_));
	spawned_skill->Initialize(GetOwner());
	cool_down_ = spawned_skill->GetCoolTime();
	duration_ = spawned_skill->GetDuration();
	is_activated_ = true;
}

bool UPassiveMechanics::IsPassiveAvailable() const
{
	return is_activated_ == false;
}
