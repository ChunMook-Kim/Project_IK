// Fill out your copyright notice in the Description page of Project Settings.


#include "Environments/SpawnMarker.h"

#include "Components/BillboardComponent.h"

// Sets default values
ASpawnMarker::ASpawnMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBillboardComponent* billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("RootComponent"));
	RootComponent = billboard;

	if (icon_texture_)
	{
		billboard->SetSprite(icon_texture_);
	}
}

// Called when the game starts or when spawned
void ASpawnMarker::BeginPlay()
{
	Super::BeginPlay();

	// Assign the sprite dynamically if not already set
	UBillboardComponent* billboard = Cast<UBillboardComponent>(RootComponent);
	if (billboard && icon_texture_)
	{
		billboard->SetSprite(icon_texture_);
	}
}

void ASpawnMarker::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	// Assign the sprite dynamically if not already set
	UBillboardComponent* billboard = Cast<UBillboardComponent>(RootComponent);
	if (billboard && icon_texture_)
	{
		billboard->SetSprite(icon_texture_);
	}
}

// Called every frame
void ASpawnMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

