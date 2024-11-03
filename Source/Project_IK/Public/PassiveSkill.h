// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PassiveSkill.generated.h"

UCLASS()
class PROJECT_IK_API APassiveSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APassiveSkill();
	void Initialize(AActor* caster);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	float cool_time_;
	float duration_;
	float hold_time_;
	AActor* caster_;
};
