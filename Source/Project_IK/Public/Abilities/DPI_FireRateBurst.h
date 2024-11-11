// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/DronePlugIn.h"
#include "DPI_FireRateBurst.generated.h"

class AGunner;
/**
 * 
 */
UCLASS()
class PROJECT_IK_API ADPI_FireRateBurst : public ADronePlugIn
{
	GENERATED_BODY()
public:
	ADPI_FireRateBurst();
	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveSkill", meta = (AllowPrivateAccess = "true"))
	float accelerate_amount_;

	AGunner* gunner_caster_;
};
