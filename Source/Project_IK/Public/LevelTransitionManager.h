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
	void OpenLevel(FName LevelName, UWorld* world);
	
	// Function be called in GameMode::BeginPlay
	UFUNCTION(BlueprintCallable)
	void PrepareLevel(UWorld* world);

protected:
	void SpawnHeroes(UWorld* world);
	void SpawnEnemies(UWorld* world);

	void SaveData();

	UPROPERTY()
	TArray<FCharacterData> data_;
};
