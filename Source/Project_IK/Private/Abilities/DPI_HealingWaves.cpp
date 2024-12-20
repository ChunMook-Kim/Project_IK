/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.16.2024
Summary : Source file for the DPI that dispatch healing waves.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/DPI_HealingWaves.h"

#include "Components/DecalComponent.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"

#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

ADPI_HealingWaves::ADPI_HealingWaves()
{
	is_periodic_ = true;
	cool_time_ = 5.f;
	duration_ = 1.f;
	hold_time_ = 0.f;

	visual_material_ = nullptr;

	decal_ = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	decal_->SetupAttachment(RootComponent);
	decal_->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
	decal_->SetVisibility(false);
	decal_->SetMobility(EComponentMobility::Movable);

	wave_radius_ = 100.f;
	heal_amount_ = 20.f;

	decal_->DecalSize = FVector(1000, wave_radius_, wave_radius_);
}

void ADPI_HealingWaves::BeginPlay()
{
	Super::BeginPlay();

	if (visual_material_)
	{
		decal_->SetDecalMaterial(visual_material_);
	}
}

void ADPI_HealingWaves::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (activated_ && left_duration_ <= 0)
	{
		FinishPassiveSkill();
	}
}

void ADPI_HealingWaves::StartPassiveSkill()
{
	Super::StartPassiveSkill();

	if (decal_)
	{
		decal_->SetVisibility(true);
	}

	PulseWave();
}

void ADPI_HealingWaves::FinishPassiveSkill()
{
	Super::FinishPassiveSkill();

	if (decal_)
	{
		decal_->SetVisibility(false);
	}
}

void ADPI_HealingWaves::PulseWave()
{
	FVector location = GetActorLocation();

	UWorld* world = GetWorld();

	// Pulses waves that heals collided characters.
	if (world)
	{
		AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(world));
		TArray<AActor*> hero_actors = game_mode->GetHeroContainers();
		for (AActor* actor : hero_actors)
		{
			FVector to_actor = actor->GetActorLocation() - location;

			// Do not consider Z component to calculate distance.
			to_actor.Z = 0.f;

			float distance_to_actor = to_actor.Size();
			if (distance_to_actor <= wave_radius_)
			{
				AUnit* unit = Cast<AUnit>(actor);
				unit->Heal(heal_amount_);
			}
		}
	}
}
