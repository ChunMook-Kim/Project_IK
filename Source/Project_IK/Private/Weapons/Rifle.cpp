/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Rifle.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Weapons/Rifle.h"
#include "Weapons/Bullet.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

ARifle::ARifle()
{
	max_megazine_ = 10;
	cur_megazine_ = 10;
	fire_interval_ = 0.3;
	reload_duration_ = 1.5;
}

void ARifle::FireWeapon(FVector target_pos, float damage)
{
	//TODO: 오브젝트 풀을 이용하면 최적화 가능.
	Super::FireWeapon(target_pos, damage);
	if(cur_megazine_ > 0)
	{
		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(muzzle_->GetComponentLocation(), target_pos);
		FActorSpawnParameters spawn_params;

		// @@ TODO: Need to discuss use it even though there are side effects.
			// While using AlwaysSpawn works, there might be Overlapping Actors, and GameplayMechanics 
				// 1. Overlapping Actors
						// It may cause physics glitches or visual artifacts
				// 2. Gameplay Mechanics
						// Spawn in obstructed areas might break immersion or functionality.
						// Such as enemies spawning inside walls.
		spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bullet_class_, muzzle_->GetComponentLocation(), rotation, spawn_params);

		if (bullet)
		{
			bullet->SetShooter(gun_owner_);
			bullet->SetDamage(damage);
			cur_megazine_--;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Spawning a bullet has failed!"));
		}
	}
}

