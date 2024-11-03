// Fill out your copyright notice in the Description page of Project Settings.


#include "PassiveSkill.h"

// Sets default values
APassiveSkill::APassiveSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APassiveSkill::Initialize(AActor* caster)
{
	PrimaryActorTick.bCanEverTick = true;
	caster_ = caster;
}

// Called when the game starts or when spawned
void APassiveSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APassiveSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

