// Fill out your copyright notice in the Description page of Project Settings.

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

/**
 * 
 */
class AActor;
class PROJECT_IK_API IGunInterface
{
	GENERATED_BODY()
	virtual void Reload() = 0;
	virtual void FireWeapon(FVector target_pos) = 0;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
