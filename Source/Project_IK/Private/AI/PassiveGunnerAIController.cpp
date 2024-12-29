/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Source file for Passive Gunner AI Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/PassiveGunnerAIController.h"

#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
APassiveGunnerAIController::APassiveGunnerAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	passive_state_key_name_ = TEXT("PassiveState");
}

// Called when the game starts or when spawned
void APassiveGunnerAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APassiveGunnerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

