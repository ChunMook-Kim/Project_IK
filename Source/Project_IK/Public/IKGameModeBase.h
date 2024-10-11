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

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetHeroContainers() noexcept;
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetEnemyContainers() noexcept;

	UFUNCTION(BlueprintCallable)
	void RemoveHero(AActor* hero);
	void RemoveEnemy(AActor* enemy);

	UFUNCTION(BlueprintCallable)
	void CheckWinLoseCondition();

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameWin();

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameLose();

protected:
	void PopulateContainers();

	TSubclassOf<AActor> hero_class_;
	TSubclassOf<AActor> enemy_class_;
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> heroes_;
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> enemies_;
};
