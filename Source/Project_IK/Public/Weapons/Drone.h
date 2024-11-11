// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

class USphereComponent;
class UDroneMechanics;

UCLASS()
class PROJECT_IK_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone", meta = (AllowPrivateAccess = "true"))
	USphereComponent* sphere_component_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh_component_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone", meta = (AllowPrivateAccess = "true"))
	UDroneMechanics* drone_mechanics_;
};
