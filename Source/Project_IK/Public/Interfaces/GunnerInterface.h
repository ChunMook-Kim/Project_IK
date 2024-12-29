/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Header file for gunner interface.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GunnerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGunnerInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_IK_API IGunnerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void StartFire(AActor* target) = 0;
	virtual void OnFire(AActor* target) = 0;
	virtual void FinishFire() = 0;
	
	virtual void Reload() = 0;
	virtual void OnReload() = 0;
	virtual void FinishReload() = 0;
	
	virtual bool IsMagazineEmpty() const = 0;
	virtual float GetFireInterval() const = 0;
	virtual float GetReloadDuration() const = 0;
};