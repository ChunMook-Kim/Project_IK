/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Header file for gun interface.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GunInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGunInterface : public UInterface
{
	GENERATED_BODY()
};

class AActor;
class PROJECT_IK_API IGunInterface
{
	GENERATED_BODY()
	virtual void Reload() = 0;
	virtual void FireWeapon(FVector target_pos) = 0;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
