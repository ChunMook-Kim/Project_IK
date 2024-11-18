/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for game mode.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "IKGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AIKGameModeBase();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	TArray<AActor*> GetHeroContainers() const noexcept;
	UFUNCTION(BlueprintPure)
	TArray<AActor*> GetEnemyContainers() const noexcept;

	UFUNCTION(BlueprintCallable)
	void RemoveHero(AActor* hero);
	UFUNCTION(BlueprintCallable)
	void RemoveEnemy(AActor* enemy);

	UFUNCTION(BlueprintCallable)
	void CheckWinLoseCondition();

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameWin();

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameLose();

	UFUNCTION()
	void RecordDamage(float damage, TWeakObjectPtr<AActor> attacker);

protected:
	void PopulateContainers();
	void DisplayCombatResult();

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> heroes_;
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> enemies_;

	UPROPERTY()
	TMap<TWeakObjectPtr<AActor>, float> gunner_damage_map_;
};
