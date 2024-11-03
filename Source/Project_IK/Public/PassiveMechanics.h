// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PassiveMechanics.generated.h"

class AGun;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UPassiveMechanics : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPassiveMechanics();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void ActivePassiveSkill();
	bool IsPassiveAvailable() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float duration_ = 0;
	float cool_down_ = 0;
	bool is_activated_ = false;
	UClass* passive_class_ = nullptr;
};
