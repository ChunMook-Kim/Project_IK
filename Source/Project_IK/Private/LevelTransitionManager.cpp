// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransitionManager.h"

#include "CharacterDataManager.h"

#include "Kismet/GameplayStatics.h"
#include "IKGameModeBase.h"
#include "Hero.h"
#include "CharacterStatComponent.h"

#include "EnemyGunner.h"

ULevelTransitionManager::ULevelTransitionManager()
	: Super::UObject()
{
}

void ULevelTransitionManager::SaveData()
{
	data_.Empty();

	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (game_mode)
	{
		TArray<AActor*> heroes = game_mode->GetHeroContainers();
		for (int32 i = 0; i < heroes.Num(); i++)
		{
			AHero* hero = Cast<AHero>(heroes[i]);
			UCharacterStatComponent* stat_component = hero->GetCharacterStatComponent();

			// @@ TODO: Need to save proper data.
			data_.Add(stat_component->GetCharacterData());
		}
	}
}

void ULevelTransitionManager::OpenLevel(FName LevelName, UWorld* world)
{
	SaveData();

	UGameplayStatics::OpenLevel(world, LevelName);
}

void ULevelTransitionManager::PrepareLevel(UWorld* world)
{
	SpawnHeroes(world);
	SpawnEnemies(world);
}

void ULevelTransitionManager::SpawnHeroes(UWorld* world)
{
	world->SpawnActor<AHero>(AHero::StaticClass(), FVector(-960, 0, 90), FRotator::ZeroRotator);
}

void ULevelTransitionManager::SpawnEnemies(UWorld* world)
{
	world->SpawnActor<AEnemyGunner>(AEnemyGunner::StaticClass(), FVector(600, 0, 90), FRotator(0, 0, 180));
}
