/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Header file for default hero.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Characters/HeroBase.h"
#include "Hero_Default.generated.h"

class UWeaponMechanics;

UCLASS()
class PROJECT_IK_API AHero_Default : public AHeroBase
{
	GENERATED_BODY()
public:
	AHero_Default();
};
