/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Header file for Passive Gunner AI Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GunnerAIController.h"
#include "PassiveGunnerAIController.generated.h"

UCLASS()
class PROJECT_IK_API APassiveGunnerAIController : public AGunnerAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APassiveGunnerAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(Blueprintable)
	void SetPassiveState(EPassiveState new_state);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunnerAIController", meta = (AllowPrivateAccess = "true"))
	FName passive_state_key_name_;
};
