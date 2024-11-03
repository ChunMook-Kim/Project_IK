// Fill out your copyright notice in the Description page of Project Settings.


#include "PassiveSkillGunner.h"
#include "PassiveMechanics.h"

APassiveSkillGunner::APassiveSkillGunner()
{
	passive_mechanics_ = CreateDefaultSubobject<UPassiveMechanics>("PassiveMechanics");
}
