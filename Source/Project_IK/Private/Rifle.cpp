/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Rifle.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Rifle.h"
#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

ARifle::ARifle()
{
	max_megazine_ = 10;
	cur_megazine_ = 10;
	fire_interval_ = 0.3;
	reload_duration_ = 1.5;
}

void ARifle::FireWeapon(FVector target_pos)
{
	//TODO: 오브젝트 풀을 이용하면 최적화 가능.
	Super::FireWeapon(target_pos);
	if(cur_megazine_ > 0)
	{
		FVector location = muzzle_->GetComponentLocation();
		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(muzzle_->GetComponentLocation(), target_pos);
		GetWorld()->SpawnActor<AActor>(bullet_class_, muzzle_->GetComponentLocation(), rotation);
		cur_megazine_--;	
	}
}

