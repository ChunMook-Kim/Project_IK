/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Header file for the DPI fire range buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/DronePlugIn.h"
#include "DPI_FireRange.generated.h"

class AUnit;
UCLASS()
class PROJECT_IK_API ADPI_FireRange : public ADronePlugIn
{
	GENERATED_BODY()
public:
	ADPI_FireRange();
	virtual void BeginPlay() override;
	virtual void StartPassiveSkill() override;
	
private:
	float buff_amount_;
	AUnit* unit_caster_;
};
