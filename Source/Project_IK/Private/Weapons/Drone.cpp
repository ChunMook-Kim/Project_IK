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
	
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}