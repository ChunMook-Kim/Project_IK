// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Drone.h"
#include "Components/DroneMechanics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADrone::ADrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	drone_mechanics_ = CreateDefaultSubobject<UDroneMechanics>("DroneMechanics");
	sphere_component_ = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	mesh_component_ = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SetRootComponent(sphere_component_);

	mesh_component_->SetupAttachment(sphere_component_);
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	//Drone은 동적으로 생성되고, AI 유닛이 동적으로 생성될 시, AI Controller는 자동으로 같이 생성되지 않는다.
	//그러므로 SpawnDefaultController 함수를 통해 AI Controller를 따로 붙여준다.
	SpawnDefaultController();
}

void ADrone::Initialize(AActor* hero)
{
	hero_ref_ = hero;
	drone_mechanics_->Initialize(hero);
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADrone::ActivateDronePlugin()
{
	drone_mechanics_->ActivateDronePlugin();
}

float ADrone::GetDronePluginHoldTime() const
{
	return drone_mechanics_->GetHoldTime();
}

bool ADrone::IsPluginAvailable() const
{
	return drone_mechanics_->IsDronePluginAvailable();
}