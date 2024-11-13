// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Hero.h"
#include "EnemyGunner.h"


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

	UFUNCTION(BlueprintCallable)
	void SetActorBlueprints(TSubclassOf<AHero> hero_blueprint, TSubclassOf<AEnemyGunner> enemy_blueprint);

protected:
	void SpawnHeroes(UWorld* world);
	void SpawnEnemies(UWorld* world);

	void SaveData();

	UPROPERTY()
	TArray<FCharacterData> data_;

	UPROPERTY()
	TSubclassOf<AHero> hero_blueprint_;
	UPROPERTY()
	TSubclassOf<AEnemyGunner> enemy_blueprint_;
};
