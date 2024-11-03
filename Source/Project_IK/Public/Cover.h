// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cover.generated.h"

class UCharacterStatComponent;
class USphereComponent;

UCLASS()
class PROJECT_IK_API ACover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACover();
	virtual void GetDamage(int damage_amount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnDie();
	
private:
	USphereComponent* cover_collider_;
	USphereComponent* cover_position_;
	UStaticMeshComponent* cover_mesh_;
	UCharacterStatComponent* character_stat_;

	bool is_broken_;
};
