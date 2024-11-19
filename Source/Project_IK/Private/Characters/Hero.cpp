/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Source file for Hero.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Hero.h"

#include "Components/SphereComponent.h"
#include "WorldSettings/IKGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/Drone.h"

AHero::AHero()
{
	drone_location_ = CreateDefaultSubobject<USphereComponent>("Drone Location");
	drone_location_->SetupAttachment(RootComponent);
}

void AHero::BeginPlay()
{
	Super::BeginPlay();
	//만약 Transform 값을 넘겨주지 않는다면 정상적으로 생성되지 않는다!
	drone_ = GetWorld()->SpawnActor<AActor>(drone_bp_class_, drone_location_->GetComponentTransform());
	Cast<ADrone>(drone_)->Initialize(this	);
	
	if(drone_ == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed To create Drone!"));
	}
	else
	{
		drone_->AttachToComponent(drone_location_, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void AHero::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

AActor* AHero::GetDrone()
{
	return drone_;
}

void AHero::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if(auto casted_drone = Cast<ADrone>(drone_))
	{
		casted_drone->Die();
	}
}

void AHero::Die()
{
	if(auto casted_drone = Cast<ADrone>(drone_))
	{
		casted_drone->Die();
	}
	AIKGameModeBase* casted_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(casted_mode) casted_mode->RemoveHero(this);
	Super::Die();
}
