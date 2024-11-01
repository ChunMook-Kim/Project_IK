/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.04.2024
Summary : Header file for Player Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IKPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AIKPlayerController();

	virtual void BeginPlay();

	UFUNCTION(BlueprintPure, Category = "Targeting")
	class UTargetingComponent* GetTargetingComponent();

	UPROPERTY(VisibleAnywhere, Category = "Targeting")
	class UTargetingComponent* targeting_component_;
};
