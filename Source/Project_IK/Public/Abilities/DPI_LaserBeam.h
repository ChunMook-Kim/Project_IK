/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.21.2024
Summary : Header file for the DPI that fire laser beams.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/DronePlugIn.h"
#include "DPI_LaserBeam.generated.h"

class AUnit;
class UNiagaraSystem;
class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API ADPI_LaserBeam : public ADronePlugIn
{
	GENERATED_BODY()
public:
	ADPI_LaserBeam();

	virtual void StartPassiveSkill() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserBeam")
	UMaterialInterface* fire_range_material_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LaserBeam")
	UNiagaraSystem* laser_niagara_system_;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	void FireLaserBeam();

	UPROPERTY()
	UDecalComponent* fire_range_decal_;

	UPROPERTY()
	UNiagaraComponent* laser_niagara_component_;

	UPROPERTY()
	float fire_rate_;

	UPROPERTY()
	float fire_range_;

	UPROPERTY()
	float damage_;

	UPROPERTY()
	float movement_speed_reduction_amount_;

	FTimerHandle fire_timer_handle_;

	AUnit* nearest_unit_;
};
