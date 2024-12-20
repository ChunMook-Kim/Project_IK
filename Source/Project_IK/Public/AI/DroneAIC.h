/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Header file for Drone AIC.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Managers/EnumCluster.h"
#include "DroneAIC.generated.h"

UCLASS()
class PROJECT_IK_API ADroneAIC : public AAIController
{
	GENERATED_BODY()
public:
	ADroneAIC();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

	UFUNCTION(Blueprintable)
	virtual void SetDPState(EDPState new_state);
	UFUNCTION(Blueprintable)
	virtual void SetDroneState(EDroneState new_state);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DroneAIController", meta = (AllowPrivateAccess = "true", BindWidget))
	UBehaviorTree* behavior_tree_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DroneAIController", meta = (AllowPrivateAccess = "true", BindWidget))
	UClass* target_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneAIController", meta = (AllowPrivateAccess = "true"))
	FName target_class_key_name_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneAIController", meta = (AllowPrivateAccess = "true"))
	FName dp_state_key_name_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneAIController", meta = (AllowPrivateAccess = "true"))
	FName drone_state_key_name_;
};
