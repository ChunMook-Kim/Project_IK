/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.12.2024
Summary : Source file for Drone Pawn.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Weapons/Drone.h"
#include "Managers/DronePluginManager.h"
#include "Components/DroneMechanics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "WorldSettings/IKGameInstance.h"

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
	//Drone은 동적으로 생성되고, AI 유닛이 동적으로 생성될 시, AI Controller는 자동으로 같이 생성되지 않는다.
	//그러므로 SpawnDefaultController 함수를 통해 AI Controller를 따로 붙여준다.
	SpawnDefaultController();
}

void ADrone::Initialize(AActor* hero)
{
	hero_ref_ = hero;
	drone_mechanics_->Initialize(hero);
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ADrone::ActivateDronePlugin()
{
	if(drone_mechanics_->IsPeriodicPluginAvailable())
	{
		drone_mechanics_->ActivatePeriodicDronePlugin();
		GetWorld()->GetTimerManager().SetTimer(dp_hold_timer_, this, &ADrone::OnPeriodicDPFinished, GetDronePluginHoldTime());
	}
}

void ADrone::OnPeriodicDPFinished()
{
	GetWorld()->GetTimerManager().ClearTimer(dp_hold_timer_);
}

void ADrone::SetPlugins(EDPType p_dp_id, EDPType g_dp_id)
{
	if(p_dp_id != EDPType::Empty)
	{
		FDPData p_dp_data = Cast<UIKGameInstance>(GetGameInstance())->GetDronePluginManager()->GetDPData(p_dp_id);
		if(p_dp_data.dp_class_ != nullptr)
		{
			drone_mechanics_->AddPeriodicPlugIn(p_dp_data.dp_class_);
		}
	}
	if(g_dp_id != EDPType::Empty)
	{
		FDPData g_dp_data = Cast<UIKGameInstance>(GetGameInstance())->GetDronePluginManager()->GetDPData(g_dp_id);
		if(g_dp_data.dp_class_ != nullptr)
		{
			drone_mechanics_->AddGeneralPlugIn(g_dp_data.dp_class_);
		}
	}
}

float ADrone::GetDronePluginHoldTime() const
{
	return drone_mechanics_->GetPeriodicPluginHoldTime();
}

bool ADrone::IsPluginAvailable() const
{
	return drone_mechanics_->IsPeriodicPluginAvailable();
}

void ADrone::Die()
{
	Destroy();
}
