// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DronePluginData.generated.h"

class PROJECT_IK_API DronePluginData
{
public:
	DronePluginData();
	~DronePluginData();
};

USTRUCT(Atomic, BlueprintType)
struct FDronePluginData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool is_empty = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName name;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* thumbnail;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UClass* dp_class;
};