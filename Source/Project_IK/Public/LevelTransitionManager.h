// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelTransitionManager.generated.h"

struct FCharacterData;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API ULevelTransitionManager : public UObject
{
	GENERATED_BODY()
public:
	ULevelTransitionManager();

	UFUNCTION(BlueprintCallable)
	void OpenLevel(FName LevelName);
	
	// Function be called in GameMode::BeginPlay
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

protected:
	void SaveData();

	UPROPERTY()
	TArray<FCharacterData> data_;
};
