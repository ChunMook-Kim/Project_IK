// Fill out your copyright notice in the Description page of Project Settings.


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
	Super::FireWeapon(target_pos);
	if(cur_megazine_ > 0)
	{
		GetWorld()->SpawnActor<ABullet>(muzzle_->GetComponentTransform().GetLocation(),
			UKismetMathLibrary::FindLookAtRotation(muzzle_->GetComponentTransform().GetLocation(), target_pos));
		cur_megazine_--;	
	}
}
