// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransitionManager.h"

#include "CharacterDataManager.h"

#include "Kismet/GameplayStatics.h"
#include "IKGameModeBase.h"
#include "Hero.h"
#include "CharacterStatComponent.h"

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

void ULevelTransitionManager::OpenLevel(FName LevelName)
{
	if (UWorld* world = GetWorld())
	{
		SaveData();

		UGameplayStatics::OpenLevel(world, LevelName);
	}
}

void ULevelTransitionManager::SpawnEnemy()
{
}
