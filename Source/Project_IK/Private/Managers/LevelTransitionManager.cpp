/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.10.2024
Summary : Source file for managing trasition between levels.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/LevelTransitionManager.h"

#include "Managers/CharacterDataManager.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"
#include "Components/CharacterStatComponent.h"

#include "Environments/SpawnMarker.h"
#include "Characters/Hero.h"
#include "Characters/EnemyGunner.h"
#include "Abilities/SkillContainer.h"

#include "Abilities/MyTestSkill.h"


ULevelTransitionManager::ULevelTransitionManager()
	: Super::UObject()
{
}

void ULevelTransitionManager::SaveData(UWorld* world)
{
	data_.Empty();

	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(world));
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
	SaveData(world);

	UGameplayStatics::OpenLevel(world, LevelName);
}

void ULevelTransitionManager::PrepareLevel(UWorld* world)
{
	SpawnHeroes(world);
	SpawnEnemies(world);
}

void ULevelTransitionManager::SetActorBlueprints(TSubclassOf<AActor> hero_blueprint, TSubclassOf<AActor> enemy_blueprint)
{
	hero_blueprint_ = hero_blueprint;
	enemy_blueprint_ = enemy_blueprint;
}

const TArray<FCharacterData>& ULevelTransitionManager::GetSavedData() const
{
	return data_;
}

void ULevelTransitionManager::SpawnHeroes(UWorld* world)
{
	TArray<AActor*> marker;
	UGameplayStatics::GetAllActorsOfClass(world, ASpawnMarker::StaticClass(), marker);
	FVector spawn_position = FVector();
	FRotator spawn_rotation = FRotator();
	if (marker.Num() > 0)
	{
		spawn_position = marker[0]->GetActorLocation();
		spawn_rotation = marker[0]->GetActorRotation();
	}

	for (int32 i = 0; i < data_.Num(); ++i)
	{
		AHero* hero = world->SpawnActor<AHero>(hero_blueprint_, spawn_position + FVector(0, (300.f * (data_.Num() - 1) / -2.f ) + (i * 300), 90), spawn_rotation);
		hero->SpawnDefaultController();
		hero->GetComponentByClass<USkillContainer>()->SetSkill(UMyTestSkill::StaticClass());
		hero->GetComponentByClass<UCharacterStatComponent>()->SetCharacterData(data_[0]);
	}
}

void ULevelTransitionManager::SpawnEnemies(UWorld* world)
{
	AEnemyGunner* enemy = world->SpawnActor<AEnemyGunner>(enemy_blueprint_, FVector(600, 0, 90), FRotator(0, 180, 0));
	enemy->SpawnDefaultController();
}
