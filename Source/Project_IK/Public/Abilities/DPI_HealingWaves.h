/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.16.2024
Summary : Source file for the DPI that dispatch healing waves.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/DronePlugIn.h"
#include "DPI_HealingWaves.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API ADPI_HealingWaves : public ADronePlugIn
{
	GENERATED_BODY()

public:
	ADPI_HealingWaves();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void StartPassiveSkill() override;
	virtual void FinishPassiveSkillAndStartCoolDown() override;
	virtual void FinishCoolDown() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealingWaves")
	UMaterialInterface* visual_material_;

private:
	void PulseWave();

	UPROPERTY()
	UDecalComponent* decal_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealingWaves", meta = (AllowPrivateAccess = "true"))
	float wave_radius_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealingWaves", meta = (AllowPrivateAccess = "true"))
	float heal_amount_;
};
