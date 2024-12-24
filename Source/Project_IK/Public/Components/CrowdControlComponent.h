/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.23.2024
Summary : Header file to manage CC(crowd control) effects.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CrowdControlComponent.generated.h"

UENUM(BlueprintType)
enum class ECCType : uint8
{
	DroneJamming UMETA(DisplayName = "DroneJamming"),
	Silence UMETA(DisplayName = "Silence"),
	ItemDisabled UMETA(DisplayName = "ItemDisabled"),
	Stun UMETA(DisplayName = "Stun"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UCrowdControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCrowdControlComponent();

	UFUNCTION(BlueprintCallable)
	void ApplyCrowdControl(ECCType cc_type, float duration);

	UFUNCTION(BlueprintCallable)
	void RemoveCrowdControl(ECCType cc_type);

	UFUNCTION(BlueprintCallable)
	void RemoveAllCrowdControl();

	UFUNCTION(BlueprintCallable)
	bool HasCrowdControl(ECCType cc_type) const;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	void DroneJamming(bool is_applying = true);
	void Silence(bool is_applying = true);
	void ItemDisabled(bool is_applying = true);
	void Stun(float duration, bool is_applying = true);

	UPROPERTY()
	TMap<ECCType, FTimerHandle> CC_timers_;
};
