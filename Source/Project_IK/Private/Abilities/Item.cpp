/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.27.2024
Summary : Source file for Item class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/Item.h"

#include "Managers/ItemDataManager.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/TextureManager.h"

#include "Characters/Unit.h"

#include "Components/TargetingComponent.h"

#include "Components/CharacterStatComponent.h"

#include "Interfaces/Damageable.h"

void UItem::InitializeItemUsingData(FItemData item_data)
{
	item_data_ = item_data;
}

void UItem::UseItem(const FTargetResult& TargetResult)
{
	switch (item_data_.item_logic_)
	{
	case EItemLogicType::None:
		break;
	case EItemLogicType::RestoreHP:
		RestoreHP(TargetResult.target_actors_[0]);
		break;
	case EItemLogicType::LaunchMissile:
		LaunchMissile(TargetResult.target_actors_);
		break;
	case EItemLogicType::AttackSpeedStimuli:
		AttackSpeedStimuli(TargetResult.target_actors_);
		break;
	default:
		break;
	}
}

FItemData UItem::GetData() const
{
	return item_data_;
}

FTargetParameters UItem::GetTargetParameters() const
{
	return FTargetParameters(item_data_.targeting_mode_, item_data_.target_type_, item_data_.range_, item_data_.radius_);
}

void UItem::RestoreHP(AActor* actor)
{
	if (!actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("UItem::RestoreHP -> Actor is invalid!!"));
		return;
	}
	TWeakObjectPtr<UCharacterStatComponent> stat = actor->GetComponentByClass<UCharacterStatComponent>();
	if (stat.IsValid())
	{
		static constexpr float heal_amount = 50.f;
		// Instant heal immediately.
		stat->Heal(heal_amount);
		int32 heal_count = 0;
		const int32 max_heal_count = 4;
		FTimerDelegate delegate;
		FTimerHandle heal_handler;
		UWorld* world = actor->GetWorld();
		if (world)
		{
			FTimerManager& timer_manager = world->GetTimerManager();
			delegate.BindLambda([stat, &heal_count, max_heal_count, &timer_manager, &heal_handler]() {
				if (!stat.IsValid())
				{
					timer_manager.ClearTimer(heal_handler);
					return;
				}
				stat->Heal(heal_amount);

				++heal_count;

				if (heal_count >= max_heal_count)
				{
					timer_manager.ClearTimer(heal_handler);
				}
				});

			timer_manager.SetTimer(heal_handler, delegate, 2.5f, true);
			
		}
	}
}

void UItem::LaunchMissile(TArray<AActor*> actors)
{
	for (int32 i = 0; i < actors.Num(); i++)
	{
		if (actors[i])
		{
			IDamageable* damageable_actor = Cast<IDamageable>(actors[i]);
			if (damageable_actor)
			{
				damageable_actor->GetDamage(50.f, nullptr);
			}
		}
	}
}

void UItem::AttackSpeedStimuli(TArray<AActor*> actors)
{
	if (actors.Num() <= 0)
	{
		return;
	}
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(actors[0]->GetWorld()));

	if (game_instance)
	{
		const UTextureManager* texture_manager = game_instance->GetTextureManager();
		if (texture_manager)
		{
			UTexture2D* texture = texture_manager->GetTexture("fire_rate_burst");
			if (texture)
			{
				for (int32 i = 0; i < actors.Num(); i++)
				{
					AUnit* unit = Cast<AUnit>(actors[i]);
					if (unit)
					{
						unit->GetCharacterStat()->ApplyBuff(FBuff(ECharacterStatType::AttackSpeed, texture, -0.25f, false, 10.f));
					}
				}
			}
		}
	}

}
