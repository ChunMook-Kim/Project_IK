/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.29.2024
Summary : Interface Header file for Unit.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UnitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUnitInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_IK_API IUnitInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void GetStunned(float stun_duration) = 0;
	virtual void OnStunned() = 0;
	virtual void FinishStun() = 0;
};
