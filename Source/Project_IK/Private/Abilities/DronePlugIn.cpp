// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/DronePlugIn.h"

ADronePlugIn::ADronePlugIn()
{
}

void ADronePlugIn::Initialize(AActor* hero)
{
	Super::Initialize(hero);
	//TODO: owner_drone_역시 어딘가에서 setting을 해줘야 한다. 하지만 여기서는 안된다.
}
