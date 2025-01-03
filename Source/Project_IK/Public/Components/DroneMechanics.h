/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Header file for Drone Mechanics component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "Abilities/DronePlugIn.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DroneMechanics.generated.h"
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UDroneMechanics : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDroneMechanics();
	void Initialize(AActor* hero);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void GetJammed(float duration);
	void FinishJam();

	//AI에서 Periodic plugin을 control하기 위한 함수들.
	float GetPeriodicPluginHoldTime() const;
	bool IsPeriodicPluginAvailable() const;

	void ActivatePeriodicDronePlugin();
	void FinishHoldTime();
	
	void AddPeriodicPlugIn(UClass* plugin_type);
	void RemovePeriodicPlugIn();

	void AddGeneralPlugIn(UClass* plugin_type);
	void RemoveGeneralPlugIn();

private:
	AActor* hero_ref_;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneMechanics", meta = (AllowPrivateAccess = "true"))
	ADronePlugIn* periodic_plugin_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneMechanics", meta = (AllowPrivateAccess = "true"))
	ADronePlugIn* general_plugin_;

	UPROPERTY(Transient)
	FTimerHandle hold_time_handle_;

	UPROPERTY(Transient)
	FTimerHandle jam_time_handle_;

	UPROPERTY(Transient)
	bool on_jammed_;
};
