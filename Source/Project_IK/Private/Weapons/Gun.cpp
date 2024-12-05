/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Gun.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Weapons/Gun.h"
#include "Components/SphereComponent.h"
#include "Components/ObjectPoolComponent.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	gun_mesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	muzzle_ = CreateDefaultSubobject<USphereComponent>(TEXT("Muzzle"));
	object_pool_component_ = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("ObjectPool"));
	
	gun_mesh_->SetCollisionProfileName(TEXT("NoCollision"));
	muzzle_->SetCollisionProfileName(TEXT("NoCollision"));

	muzzle_->SetupAttachment(gun_mesh_);
	muzzle_->SetVisibility(false);

	SetRootComponent(gun_mesh_);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::Reload()
{
	cur_megazine_ = max_megazine_;
}

void AGun::FireWeapon(FVector target_pos, float damage)
{
}

bool AGun::IsMagazineEmpty() const
{
	return cur_megazine_ <= 0;
}

float AGun::GetFireInterval() const
{
	return fire_interval_;
}

void AGun::SetFireInterval(float Fire_Interval)
{
	fire_interval_ = Fire_Interval;
}

float AGun::GetReloadDuration() const
{
	return reload_duration_;
}

void AGun::SetReloadDuration(float Reload_Duration)
{
	reload_duration_ = Reload_Duration;
}

void AGun::SetGunOwner(TWeakObjectPtr<AActor> gun_owner)
{
	gun_owner_ = gun_owner;
}
