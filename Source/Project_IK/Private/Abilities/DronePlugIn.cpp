// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/DronePlugIn.h"
#include "Characters/Hero.h"

ADronePlugIn::ADronePlugIn()
{
}

void ADronePlugIn::Initialize(AActor* caster)
{
	Super::Initialize(caster);
	owner_drone_ = Cast<AHero>(caster)->GetDrone();
}
