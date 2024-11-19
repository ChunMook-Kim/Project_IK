/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Header file for Drone Pawn.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
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
	virtual void Initialize(AActor* hero);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ActivateDronePlugin();
	float GetDronePluginHoldTime() const;
	bool IsPluginAvailable() const;
	void Die();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drone", meta = (AllowPrivateAccess = "true", BindWidget))
	USphereComponent* sphere_component_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drone", meta = (AllowPrivateAccess = "true", BindWidget))
	UStaticMeshComponent* mesh_component_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drone", meta = (AllowPrivateAccess = "true", BindWidget))
	UDroneMechanics* drone_mechanics_;

	AActor* hero_ref_;
};
