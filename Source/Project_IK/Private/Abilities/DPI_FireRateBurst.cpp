// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/DPI_FireRateBurst.h"
#include "Characters/Gunner.h"
#include "Components/CharacterStatComponent.h"

ADPI_FireRateBurst::ADPI_FireRateBurst()
{
	cool_time_ = 5.f;
	duration_ = 2.f;
	hold_time_ = 0.f;
}

void ADPI_FireRateBurst::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(gunner_caster_ == nullptr) gunner_caster_ = Cast<AGunner>(caster_);
	//공속 가속 로직 적용.
	duration_ -= DeltaSeconds;
	if(duration_ < 0) Destroy();
}
