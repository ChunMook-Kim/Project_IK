/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Header file for passive caster.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PassiveCaster.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPassiveCaster : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_IK_API IPassiveCaster
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ActivatePassive() = 0;
	virtual bool IsPassiveAvailable() = 0;
	virtual float GetPassiveHoldTime() = 0;
};
