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
#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/HeroSelect/IKHeroSelectMode.h"
#include "Components/CharacterStatComponent.h"

#include "Environments/SpawnMarker.h"
#include "Characters/HeroBase.h"
#include "Characters/EnemyBase.h"
#include "Abilities/SkillContainer.h"

#include "Abilities/MyTestSkill.h"
#include "UI/IKMaps.h"


ULevelTransitionManager::ULevelTransitionManager()
	: Super::UObject()
{
}

void ULevelTransitionManager::OpenLevel(UWorld* world, FIntPoint map_position)
{
	SaveData(world);

	UIKGameInstance* instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(world));
	FMapNode node = instance->GetMapPtr()->GetNode(map_position.X, map_position.Y);
	switch (node.type)
	{
	case NodeType::None:
		UE_LOG(LogTemp, Warning, TEXT("ULevelTransitionManager::OpenLevel -> Tried to go to invalid map node"));
		break;
	case NodeType::Enemy:
		UGameplayStatics::OpenLevel(world, FName("CombatLevel"));
		instance->GetMapPtr()->SetPlayerGridPosition(map_position);
		break;
	default:
		break;
	}
}

void ULevelTransitionManager::SaveData(UWorld* world)
{
	data_.Empty();

	UIKGameInstance* instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(world));
	AGameModeBase* raw_game_mode = UGameplayStatics::GetGameMode(world);
	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(raw_game_mode);
	if (game_mode)
	{
		TArray<AActor*> heroes = game_mode->GetHeroContainers();
		for (int32 i = 0; i < heroes.Num(); i++)
		{
			AHeroBase* hero = Cast<AHeroBase>(heroes[i]);
			const UCharacterStatComponent* stat_component = hero->GetCharacterStat();

			// @@ TODO: Need to save proper data.
			data_.Add(stat_component->GetCharacterData());
		}
		return;
	}
	AIKHeroSelectMode* hero_select_mode = Cast<AIKHeroSelectMode>(raw_game_mode);
	if (hero_select_mode)
	{
		// @@ TODO : Save selected hero data rather than hard coded one.
				// Currently, save 4 stat data directly. Doesn't make sense.
		for (int32 i = 0; i < 4; i++)
		{
			data_.Add(*instance->GetCharacterDataManager()->GetCharacterData(0));
		}
	}
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
		AHeroBase* hero = world->SpawnActor<AHeroBase>(hero_blueprint_, spawn_position + FVector(0, (300.f * (data_.Num() - 1) / -2.f ) + (i * 300), 90), spawn_rotation);
		hero->SpawnDefaultController();
		hero->GetComponentByClass<USkillContainer>()->SetSkill(UMyTestSkill::StaticClass());
		hero->GetComponentByClass<UCharacterStatComponent>()->SetCharacterData(data_[0]);
		hero->Initialize();
	}
}

void ULevelTransitionManager::SpawnEnemies(UWorld* world)
{
	AEnemyBase* enemy = world->SpawnActor<AEnemyBase>(enemy_blueprint_, FVector(600, 0, 90), FRotator(0, 180, 0));
	enemy->SpawnDefaultController();
}
