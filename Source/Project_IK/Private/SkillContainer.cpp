// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillContainer.h"

// Sets default values for this component's properties
USkillContainer::USkillContainer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
}

void USkillContainer::InitializeComponent()
{
	if (skill_class_)
	{
		skill_ = NewObject<USkillBase>(this, skill_class_);
	}
}

void USkillContainer::InvokeSkills()
{
	skill_->ActivateSkill();
}


// Called when the game starts
void USkillContainer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
