// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/DronePlugIn.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DroneMechanics.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UDroneMechanics : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDroneMechanics();
	void Initialize(AActor* hero);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ActivateDronePlugin();
	float GetHoldTime() const;
	bool IsDronePluginAvailable() const;
	
	// void AddPlugIn(int idx, UClass* plugin_type);
	// void RemovePlugIn(int idx);

private:
	AActor* hero_ref_;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneMechanics", meta = (AllowPrivateAccess = "true"))
	ADronePlugIn* plugin_;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneMechanics", meta = (AllowPrivateAccess = "true"))
	UClass* plug_in_class_;
};