// Fill out your copyright notice in the Description page of Project Settings.


#include "Cover.h"
#include "Components/SphereComponent.h"
#include "CharacterStatComponent.h"
// Sets default values
ACover::ACover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	cover_collider_ = CreateDefaultSubobject<USphereComponent>(FName("cover_collider"));
	cover_position_ = CreateDefaultSubobject<USphereComponent>(FName("cover_position"));
	cover_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(FName("cover_mesh"));
	character_stat_ = CreateDefaultSubobject<UCharacterStatComponent>(FName("character_stat"));
	SetRootComponent(cover_collider_);
}

// Called when the game starts or when spawned
void ACover::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACover::GetDamage(int damage_amount)
{
	character_stat_->GetDamage(damage_amount);
}

void ACover::OnDie()
{
	is_broken_ = true;
	Destroy();
}
