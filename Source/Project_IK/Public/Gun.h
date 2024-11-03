// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunInterface.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class PROJECT_IK_API AGun : public AActor, public IGunInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
	virtual void Reload() override;
	virtual void FireWeapon(FVector target_pos) override;

private:
	int max_megazine_ = 0;
	int cur_megazine_ = 0;
	float fire_interval_ = 0;
	float reload_duration_ = 0;
};
