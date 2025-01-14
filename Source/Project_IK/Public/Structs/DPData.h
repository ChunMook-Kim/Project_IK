// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Managers/EnumCluster.h"
#include "Managers/RarityAbstractObject.h"
#include "DPData.generated.h"

USTRUCT()
struct PROJECT_IK_API FDPData : public FRarityData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DronePlugin")
	bool is_periodic_ = false;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DronePlugin")
	UClass* dp_class_ = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DronePlugin")
	EDPType dp_type_ = EDPType::Empty;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DronePlugin")
	UTexture2D* dp_icon_ = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DronePlugin")
	FString dp_description_ = TEXT("Empty");
};