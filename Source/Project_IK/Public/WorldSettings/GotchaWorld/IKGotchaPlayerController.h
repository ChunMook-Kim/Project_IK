/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.08.2025
Summary : Header file for Player Controller in GotchaLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IKGotchaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKGotchaPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
