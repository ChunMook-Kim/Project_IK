/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Header file for the DPI fire rate burst.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Abilities/DronePlugIn.h"
#include "DPI_FireRateBurst.generated.h"

class AUnit;
UCLASS()
class PROJECT_IK_API ADPI_FireRateBurst : public ADronePlugIn
{
	GENERATED_BODY()
public:
	ADPI_FireRateBurst();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void StartPassiveSkill() override;
	virtual void FinishPassiveSkill() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PassiveSkill", meta = (AllowPrivateAccess = "true"))
	float accelerate_amount_;

	AUnit* unit_caster_;
};
