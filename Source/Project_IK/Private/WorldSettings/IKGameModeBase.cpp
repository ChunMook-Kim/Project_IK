/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Source file for game mode.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/IKGameModeBase.h"

#include "Kismet/GameplayStatics.h"

#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKPlayerController.h"
#include "Components/TargetingComponent.h"
#include "Managers/LevelTransitionManager.h"

#include "WorldSettings/IKHUD.h"


#include "Characters/HeroBase.h"

AIKGameModeBase::AIKGameModeBase()
	: Super::AGameModeBase()
{
}

void AIKGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (game_instance)
	{
		ULevelTransitionManager* level_transition_manager = game_instance->GetLevelTransitionManager();
		if (level_transition_manager)
		{
			level_transition_manager->PrepareLevel(GetWorld());
		}
	}
	PopulateContainers();
}

TArray<AActor*> AIKGameModeBase::GetHeroContainers() const noexcept
{
	return heroes_;
}

TArray<AActor*> AIKGameModeBase::GetEnemyContainers() const noexcept
{
	return enemies_;
}

void AIKGameModeBase::RemoveHero(AActor* hero)
{
	if (hero)
	{
		heroes_.Remove(hero);
		CheckWinLoseCondition();
	}
}

void AIKGameModeBase::RemoveEnemy(AActor* enemy)
{
	if (enemy)
	{
		enemies_.Remove(enemy);
		CheckWinLoseCondition();
	}
}

void AIKGameModeBase::CheckWinLoseCondition()
{
	// Escape immediately if any side is not annihilated.
	if (enemies_.Num() > 0 && heroes_.Num() > 0)
	{
		return;
	}

	DisplayCombatResult();
	AIKPlayerController* pc = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	pc->GetTargetingComponent()->StopTargeting();

	if (enemies_.Num() <= 0)
	{
		OnGameWin();
	}
	else if (heroes_.Num() <= 0)
	{
		OnGameLose();
	}
}

void AIKGameModeBase::RecordDamage(float damage, TWeakObjectPtr<AActor> attacker)
{
	if (Cast<AHeroBase>(attacker))
	{
		if (gunner_damage_map_.Contains(attacker))
		{
			gunner_damage_map_[attacker] += damage;
		}
		else
		{
			gunner_damage_map_.Add(attacker, damage);
		}
	}
}

void AIKGameModeBase::PopulateContainers()
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(this));
	
	if (game_instance)
	{
		// Populate a hero container
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), game_instance->hero_blueprint_, heroes_);

		// Populate an enemy container
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), game_instance->enemy_blueprint_, enemies_);
	}
}

void AIKGameModeBase::DisplayCombatResult()
{
	APlayerController* player_controller = GetWorld()->GetFirstPlayerController();
	
	if (player_controller)
	{
		AIKHUD* hud = Cast<AIKHUD>(player_controller->GetHUD());
		if (hud)
		{
			hud->DisplayCombatResult(heroes_, gunner_damage_map_);
		}
	}
}
