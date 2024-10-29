/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for game mode.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "IKGameModeBase.h"

#include "Kismet/GameplayStatics.h"

#include "Project_IK/Public/IKHUD.h"

AIKGameModeBase::AIKGameModeBase()
	: Super::AGameModeBase()
{
	PopulateContainers();
}

void AIKGameModeBase::BeginPlay()
{
	Super::BeginPlay();
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
	if (enemies_.Num() <= 0)
	{
		OnGameWin();
	}
	else if (heroes_.Num() <= 0)
	{
		OnGameLose();
	}
}

void AIKGameModeBase::PopulateContainers()
{
	// Populate a hero container
	ConstructorHelpers::FClassFinder<AActor> BP_Hero_Finder(TEXT("/Game/__BluePrints/BP_Hero"));
	if (BP_Hero_Finder.Succeeded())
	{
		hero_class_ = BP_Hero_Finder.Class;
	}
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), hero_class_, heroes_);

	// Populate an enemy container
	ConstructorHelpers::FClassFinder<AActor> BP_Enemy_Finder(TEXT("/Game/__BluePrints/BP_Enemy"));
	if (BP_Enemy_Finder.Succeeded())
	{
		enemy_class_ = BP_Enemy_Finder.Class;
	}
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), enemy_class_, enemies_);
}
